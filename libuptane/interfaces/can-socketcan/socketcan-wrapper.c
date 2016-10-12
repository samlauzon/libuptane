
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdarg.h>
#include <signal.h>
#include <fcntl.h>

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
	STATUS_SEND_REQUEST,
	STATUS_ACK_OUI,  // Snooty CAN channel 
	STATUS_ACK_NON,  // Oh non!! 
	STATUS_UPLOADING,
	STATUS_DOWNLOADING,
	STATUS_NEXT,
	STATUS_COMPLETE
} status_t; 

// Module Specific 
int can_sock; 			// Can Socket Handle
int isotp_sock;		// ISO-TP Socket Handle
struct sockaddr_can addr_isotp; 
struct sockaddr_can addr_can;
struct ifreq ifr;

pthread_t th_status; // Status Thread Handle
pthread_t th_read; // Read Thread Handle
pthread_t th_isotp; // ISO-TP Thread Handle

int s_status = 0;  // Thread control (status) 
int s_read = 0;    // Thread control (read) 
int s_isotp = 0; 

int status_id = 1; // The CAN ID we broadcast our status on
status_t status = STATUS_ONLINE; 


int num_targets = 0; 
int *target_ids = NULL; 
char *cfg_str = NULL; 

// Forward Declarations 
void socketcan_send_status( unsigned int status_id ) ;
void socketcan_read( void ) ;
void socketcan_isotp_transmit( int target, char *data, int size ); 
void socketcan_isotp_receive( void ); 


//
// init 
//
void init_socketcan( void ) 
{

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

	 // This is what it's relying on now 
	//addr_isotp.can_addr.tp.tx_id = 1537;  // NOT GOOD ? 
	//addr_isotp.can_addr.tp.rx_id = 513;  // NOT GOOD . 

	//if( bind(isotp_sock, (struct sockaddr *)&addr_isotp, sizeof(addr_can)) < 0) 
	//{ 
	//	perror("bind isotp");
	//	return 1; 
	//}

	addr_can.can_family = AF_CAN;
	addr_can.can_ifindex = ifr.ifr_ifindex;

	if (bind(can_sock, (struct sockaddr *)&addr_can, sizeof(addr_can)) < 0) 
	{
		perror("bind");
		return 1;
	}

	int val = 1;
	setsockopt(isotp_sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	setsockopt(can_sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)); 

	num_targets = get_config_int("socketcan.num_targets");

	if(num_targets == -1)  // If not defined 
		num_targets = 0; 

	target_ids = (int *)malloc( (size_t)num_targets ); 
	cfg_str = (char *)malloc( (size_t)strlen("socketcan.target_id_9999")); // haha.
	
	fprintf(stderr, "[can-socketcan|read] %d targets defined in the config file\n", num_targets); 

	for( int i = 1; i <= num_targets; i++ )  
	{
		sprintf(cfg_str, "socketcan.target_id_%d", i); 
		target_ids[i] = get_config_int(cfg_str);  
		fprintf(stderr, "[can-socketcan|read] Looking for 0x%x\n", target_ids[i]);
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
	status_id = get_config_int("socketcan.status_id"); 

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
	//fprintf(stderr, "Status thread returned %d\n", s_status); 

	pthread_join(th_read, NULL); 
	//fprintf(stderr, "Read thread returned %d\n", s_read); 

}

//
// send_raw_frame 
//   id, dlc, byte[dlc], byte[dlc-1] ... 
//  
//  Caution: Doesn't verify data 
//
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

//
// Fix me. 
//
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

//
// Send a status message
//
void socketcan_send_status( unsigned int status_id ) 
{
	while( s_status ) 
	{
		send_raw_frame( status_id & 0x7FF, 4, 0, 0, 0, status ); 
		//usleep(100000); 
		// This is too long because of the send_raw_frame overhead. 
		usleep(249900); 
	}
	pthread_exit(s_status);  // Poor reuse
}



//
// socketcan_read
//   A Read thread to poll the CAN channel
//    set s_read to have the thread exit 
//
void socketcan_read( void ) 
{
	struct canfd_frame frame;
	struct canfd_frame *recv_buf; 

	int nbytes; 

	recv_buf = (struct canfd_frame *)malloc(sizeof(struct canfd_frame) * num_targets); 
	memset(recv_buf, 0, sizeof(struct canfd_frame) * num_targets); 


	int debug_framedump = get_config_int("socketcan.debug");

	int flags = fcntl(can_sock, F_GETFL, 0);
	fcntl(can_sock, F_SETFL, flags | O_NONBLOCK);



	while(s_read) 
	{
		nbytes = read(can_sock, &frame, sizeof(struct can_frame));

		if (nbytes < 0 || nbytes == -1 ) {
			continue; // Bad idea. 
		}

		if (nbytes < sizeof(struct can_frame)) {
			fprintf(stderr, "read: incomplete CAN frame\n");
			continue;  // Bad Idea. 
		}

		// Act like a jerk if you define stuff in the config file 
		if(debug_framedump != -1) 
		{
			fprintf(stderr, "Frame: [0x%X] [%d] \n", frame.can_id, frame.len); 
			for(int i = 0; i <= frame.len-1; i++)
				fprintf(stderr, "0x%.2X ", frame.data[i]&0xFF); 
			fprintf(stderr, "\n"); 
		}

		// Parse list of targets 
		for(int n = 0; n <= num_targets; n++) 
		{
			// If we found a matching ID 
			if( frame.can_id == target_ids[n] ) 
			{
				if( recv_buf[n].data[0] != frame.data[0] || recv_buf[n].data[1] != frame.data[1] ||
						recv_buf[n].data[2] != frame.data[2] || recv_buf[n].data[3] != frame.data[3] )
				{ 
					fprintf(stderr, "[can-socketcan|read] target 0x%X has status %d\n", target_ids[n], frame.data[3]); 
					// wish memcpy worked 
					recv_buf[n].data[0] = frame.data[0] ;
					recv_buf[n].data[1] = frame.data[1] ;
					recv_buf[n].data[2] = frame.data[2] ;
					recv_buf[n].data[3] = frame.data[3]  ;
				}
			}
		}


	}
	////
	//  These get flagged as a double free at runtime. 
	//    .. I'll take it's word for it, I guess.
	//free(target_ids); 
	//free(cfg_str);

	free(recv_buf);

	pthread_exit(s_read); 
}

void socketcan_isotp_transmit( int target, char *data, int size )
{
	addr_isotp.can_family = AF_CAN;
	addr_isotp.can_ifindex = ifr.ifr_ifindex; 
	addr_isotp.can_addr.tp.tx_id = status_id +1;  // One above status
	addr_isotp.can_addr.tp.rx_id = target_ids[target] + 1; 

	//fprintf(stderr, " Tx: %d Rx: %d \n", addr_isotp.can_addr.tp.tx_id, addr_isotp.can_addr.tp.rx_id); 
	if( bind(isotp_sock, (struct sockaddr *)&addr_isotp, sizeof(addr_can)) < 0) 
	{ 
		perror("bind isotp");
		return 1; 
	}

	send_raw_isotp();

}

void socketcan_isotp_receive( void ) 
{
   unsigned char msg[5000]; // 4095 max anyway? 
   int nbytes;

	addr_isotp.can_family = AF_CAN;
	addr_isotp.can_ifindex = ifr.ifr_ifindex; 
	addr_isotp.can_addr.tp.tx_id = 0x601;  // One above status
	addr_isotp.can_addr.tp.rx_id = 0x201;  

	//fprintf(stderr, " Tx: %d Rx: %d \n", addr_isotp.can_addr.tp.tx_id, addr_isotp.can_addr.tp.rx_id); 
	if( bind(isotp_sock, (struct sockaddr *)&addr_isotp, sizeof(addr_can)) < 0) 
	{ 
		perror("bind isotp");
		return 1; 
	}

	do {
		nbytes = read(isotp_sock, msg, 5000);
		if (nbytes > 0 && nbytes < 5000)
			for (int i=0; i < nbytes; i++)
				printf("%02X ", msg[i]);
		printf("\n");
	} while (0);
}


