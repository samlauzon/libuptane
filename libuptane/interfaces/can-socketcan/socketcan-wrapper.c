
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdarg.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>


#include <linux/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/can/isotp.h>

#include "config.h"

// Things that shouldn't be here
typedef enum StatusByte {  // Sure. 
	STATUS_ONLINE = 1, 
	STATUS_READY,
	STATUS_DOWNLOADING,
	STATUS_COMPLETE
} status_t; 

// Module Specific 
int can_sock; 			// Can Socket Handle
int isotp_sock;		// ISO-TP Socket Handle

pthread_t th_status; // Status Thread Handle
pthread_t th_read; // Read Thread Handle

int s_status = 0;  // Thread control (status) 
int s_read = 0;    // Thread control (read) 

status_t status = STATUS_ONLINE; 

// Forward Declarations 
void socketcan_send_status( unsigned int status_id ) ;
void socketcan_read( void ) ;


//
// init 
//
void init_socketcan( void ) 
{
	struct ifreq ifr;
	struct sockaddr_can addr_isotp; 
	struct sockaddr_can addr_can;

	isotp_sock = socket(PF_CAN, SOCK_DGRAM, CAN_ISOTP);
	can_sock = socket(PF_CAN, SOCK_RAW, CAN_RAW); 

	if( (isotp_sock < 0) ) 
		fprintf(stderr, "Cannot open ISO-TP socket\n");

	if( (can_sock < 0) ) 
		fprintf(stderr, "Cannot open CAN socket\n"); 

	strcpy(ifr.ifr_name, get_config_string("socketcan.interface"));
	ifr.ifr_name[5] = '\0';

	ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);
	if (!ifr.ifr_ifindex) 
	{
		error("if_nametoindex");
		return 1;
	}

	addr_isotp.can_family = AF_CAN;
	addr_isotp.can_ifindex = ifr.ifr_ifindex; 
	addr_isotp.can_addr.tp.tx_id = 0xFFE;  // NOT GOOD ? 
	addr_isotp.can_addr.tp.rx_id = 0xF0E;  // NOT GOOD . 
	

	if( bind(isotp_sock, (struct sockaddr *)&addr_isotp, sizeof(addr_can)) < 0) 
	{ 
		perror("bind isotp");
		return 1; 
	}

	addr_can.can_family = AF_CAN;
	addr_can.can_ifindex = ifr.ifr_ifindex;

	if (bind(can_sock, (struct sockaddr *)&addr_can, sizeof(addr_can)) < 0) 
	{
		perror("bind");
		return 1;
	}

	// RESET the device in the event of prior disconnection 

	// ifr.ifr_flags &= ~IFF_UP;
	// ioctl(can_sock, SIOCSIFFLAGS, &ifr); 

   // struct ifreq ift; 
	// ioctl(can_sock, SIOCGIFFLAGS, &ift); 
	//  if( ift.ifr_flags == IFF_UP ) { fprintf(stderr, "\nUp\n"); }
	//  else { fprintf(stderr, "\nDown\n");  }

	// ifr.ifr_flags |= IFF_UP;
	// ioctl(can_sock, SIOCSIFFLAGS, &ifr); 

	// ioctl(can_sock, SIOCGIFFLAGS, &ift); 
	//  if( ift.ifr_flags == IFF_UP ) { fprintf(stderr, "\nUp\n"); }
	// else { fprintf(stderr, "\nDown\n");  }

	////////////// 
	// The above reset code always returns 'down' 
	// even when run as root.  No idea how to determine state of the bus (!)
	//
	
	// Setup the status message 
	int status_id = get_config_int("socketcan.status_id"); 

	s_status = 1;
	if(  pthread_create( &th_status, NULL, socketcan_send_status, status_id ) ) 
	{
		fprintf(stderr, "[can-socketcan] Could not create status thread\n"); 
		s_status = 0; 
	}

	s_read = 1;
	if( pthread_create( &th_read, NULL, socketcan_read ) )
	{
		fprintf(stderr, "[can-socketcan] Couild not create read thread\n"); 
		s_read = 0; 
	}
	

}

//
// cleanup 
//
void fini_socketcan( void ) 
{
	s_status = 0; 
	s_read = 0; 

   // Wrangle in the status thread
	pthread_join(th_status, NULL); 
	pthread_join(th_read, NULL); 
}


void send_raw_frame( int id, int dlc, ... )
{
	struct canfd_frame frame; 
	va_list db;

	frame.can_id = id; 
	frame.len = dlc; 

	va_start(db, dlc);
	for(int i = 0; i <= dlc-1; i++) 
		frame.data[i] = va_arg(db, int); 

	va_end(db); 

	write(can_sock, &frame, CAN_MTU);
}

void send_raw_isotp( ) 
{
	char *buf; 
	char *filename = "metadata.ber";
	FILE *f = fopen(filename, "r");
	if( f == NULL )
	{
		fprintf(stderr, "Cannot open file \"%s\" - Exiting.\n", filename);
		return; 
	}

	fseek(f, 0, SEEK_END);
	int filesize = ftell(f);
	buf = (char *) malloc((size_t)filesize + 1);
	memset(buf, 0, filesize + 1);
	rewind(f);
	size_t size = fread(buf, 1, filesize, f);

	if(size == 0 || size > filesize ) 
	{
		fprintf(stderr, "%s: Too large input\n", filename);
		return;
	}

	write(isotp_sock, buf, filesize);  
	fclose(f); 
}

void socketcan_send_status( unsigned int status_id ) 
{
	while( s_status ) 
	{
		send_raw_frame( status_id & 0x7FF, 4, 0, 0, 0, status ); 
 	  //usleep(100000); 
	  // This is too long because of the send_raw_frame overhead. 
		usleep(99900); 
	}
	pthread_exit(s_status);  // Poor reuse
}

void socketcan_read( void ) 
{
	struct canfd_frame frame;

	int nbytes ; 

	while(s_read) 
	{
		nbytes = read(can_sock, &frame, sizeof(struct can_frame));

		if (nbytes < 0) {
			perror("can raw socket read");
			continue; // Bad idea. 
		}

		if (nbytes < sizeof(struct can_frame)) {
			fprintf(stderr, "read: incomplete CAN frame\n");
			continue;  // Bad Idea. 
		}

		fprintf(stderr, "Frame: [0x%X] [%d] ", frame.can_id, frame.len); 
	   for(int i = 0; i <= frame.len-1; i++)
			fprintf(stderr, "0x%.2X ", frame.data[i]&0xFF); 

		fprintf(stderr, "\n"); 

	}
	pthread_exit(s_read); 
}
