
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
#include <linux/can/error.h> 
#include <linux/can/raw.h>
#include <linux/can/isotp.h>

#include "config.h"

// Things that shouldn't be here
//   ............. These have terrible names. 
typedef struct isotp_header_frame 
{
	int magic_number;
	int data_type;
	int total_size;
   int frame_count; 
	char filename[128]; // ugh. 
} isotp_header_t; 

#define MAGIC_NUMBER 0x55707448  // "UptH"

typedef enum DataType { 
	METADATA = 0,
	IMAGEDATA,
	IRRELEVANT_DATA		// Relevant?
} datatype_t; 

typedef enum StatusByte {  // Sure. 
	STATUS_OFFLINE = 0,
	STATUS_ONLINE = 1, 
	STATUS_SEND_REQUEST,
	STATUS_UPLOADING,
	STATUS_DOWNLOADING,
	STATUS_NEXT,
	STATUS_COMPLETE
} status_t; 

#define STATUS_BYTE 3

// This stuff is probably supposed to be here :: 

// Module Specific 
int can_sock; 			// Can Socket Handle
int isotp_sock;		// ISO-TP Socket Handle
struct sockaddr_can addr_isotp; 
struct sockaddr_can addr_can;
struct ifreq ifr;

pthread_t th_status; // Status Thread Handle
pthread_t th_read; // Read Thread Handle
pthread_t th_isotp; // ISO-TP Thread Handle
pthread_t th_tprecv;  // ISO-TP Receive 

int s_status = 0;  // Thread control (status) 
int s_read = 0;    // Thread control (read) 
int s_isotp = 0;   // Send 
int s_tprecv = 0;  // Receive

int status_id = 1; // The CAN ID we broadcast our status on

struct canfd_frame *recv_buf; 

struct canfd_frame status_frame; 

int num_targets = 0; 
int *target_ids = NULL; 
char *cfg_str = NULL; 

// Forward Declarations 
void socketcan_send_status( unsigned int status_id ) ;
void socketcan_read( void ) ;
void send_isotp_file( int target, int data_type, char *filename );
void socketcan_isotp_receive( int target, char *dest, int *size ); 
void socketcan_flush_status( ); 

int check_status( int target ) { 

	if(target <= num_targets ) 
		return recv_buf[target].data[3]; 
	else
		return -1;
} 

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
	static struct can_isotp_options opts;
	opts.frame_txtime = 250000;
	opts.flags |= CAN_ISOTP_FORCE_TXSTMIN;
	int force_tx_stmin = 250000; 
	setsockopt(isotp_sock, SOL_CAN_ISOTP, CAN_ISOTP_OPTS, &opts, sizeof(opts));
	setsockopt(isotp_sock, SOL_CAN_ISOTP, CAN_ISOTP_TX_STMIN, &force_tx_stmin, sizeof(force_tx_stmin));

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

	can_err_mask_t err_mask = 0x1FF; // All errors

	setsockopt(can_sock, SOL_CAN_RAW, CAN_RAW_ERR_FILTER, &err_mask, sizeof(err_mask)); 

//	int recv_own_msgs = 1; 
//	setsockopt(can_sock, SOL_CAN_RAW, CAN_RAW_RECV_OWN_MSGS,
//			&recv_own_msgs, sizeof(recv_own_msgs));


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

	s_tprecv = 1; 
	if( pthread_create( &th_tprecv, NULL, socketcan_isotp_receive, 1, NULL, NULL ) ) 
	{
	  fprintf(stderr, "[can-socketcan] Could not create iso-tp receive thread\n"); 
		s_tprecv = 0;
	}

		// Set Status to ONLINE
	status_frame.data[STATUS_BYTE] = STATUS_ONLINE; 
   socketcan_flush_status(); 
}

//
// cleanup 
//
void fini_socketcan( void ) 
{
	status_frame.data[STATUS_BYTE] = STATUS_OFFLINE; 
   socketcan_flush_status(); 

	s_status = 0; 
	s_read = 0; 

	// Wrangle in the status thread
	pthread_join(th_status, NULL); 
	//fprintf(stderr, "Status thread returned %d\n", s_status); 

	pthread_join(th_read, NULL); 
	//fprintf(stderr, "Read thread returned %d\n", s_read); 

	close(can_sock);
	close(isotp_sock);
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
void send_isotp_file( int target, int data_type, char *filename ) 
{
	addr_isotp.can_family = AF_CAN;
	addr_isotp.can_ifindex = ifr.ifr_ifindex; 
	addr_isotp.can_addr.tp.tx_id = status_id +1;  // One above status
	addr_isotp.can_addr.tp.rx_id = target_ids[target] + 1; 

	int p;

	while(1) 
	{
		if( recv_buf != NULL ) {
			p = recv_buf[target].data[3];
		}

		if( p == 1 )
			break;
	}
	fprintf(stderr, " Tx: %d Rx: %d \n", addr_isotp.can_addr.tp.tx_id, addr_isotp.can_addr.tp.rx_id); 
	if( bind(isotp_sock, (struct sockaddr *)&addr_isotp, sizeof(addr_can)) < 0) 
	{ 
		perror("bind isotp");
		return 1; 
	}

	status_frame.data[STATUS_BYTE] = STATUS_UPLOADING; 
	char *buf; 
	FILE *f = fopen(filename, "r");
	if( f == NULL )
	{
		fprintf(stderr, "Cannot open file \"%s\" \n", filename);
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

	// figure out how large the payload is in total, 
	//   (Each packet is 4090 max, Any leftover needs it's own packet.. 
	status_frame.data[2] = size / 4090; 
	if( size % 4090 ) { status_frame.data[2]++; } // roundup. 

	// Use this to count, too .. 
	int frames = status_frame.data[2]; 

	// Setup a header to tell the target what it's going to be getting
	// 
	isotp_header_t *header = (isotp_header_t *)malloc((size_t)sizeof(isotp_header_t));  
	// TODO: Check the return 
	
	header->magic_number = MAGIC_NUMBER; 
	header->data_type = data_type; 
	header->total_size = size;
	header->frame_count = frames;
	snprintf(header->filename, 255, filename); 
	write( isotp_sock, header, sizeof(isotp_header_t)); 
	free(header);

	int datasent = 0; 
	for( ; status_frame.data[2] >= 1; status_frame.data[2]-- ) 
	{
		fprintf(stderr, "Writing %d of %d\n", datasent, size); 
		if(size - datasent <= 4090) 
		{
			write(isotp_sock, buf + datasent, (size-datasent));
			datasent += (size-datasent); 
		}
		else
		{
			write(isotp_sock, buf + datasent, 4090);  
			datasent += 4090; 
		}
		
	}
   fprintf(stderr, " Sent %d bytes.\n ", datasent); 
	status_frame.data[STATUS_BYTE] = STATUS_ONLINE; 
   socketcan_flush_status( );
	fclose(f); 
}

// 
// Force a message out without waiting for the cyclic period
//    Handy for things that occur off-period
//     .. like iso-tp sessions, or exiting 
//
void socketcan_flush_status( ) 
{
	send_raw_frame( status_id & 0x7FF, 4, status_frame.data[0], 
			status_frame.data[1], status_frame.data[2], status_frame.data[3] );
}


//
// Send a status message
//
void socketcan_send_status( unsigned int status_id ) 
{
	while( s_status ) 
	{
		send_raw_frame( status_id & 0x7FF, 4, 0, 0, status_frame.data[2], status_frame.data[3] ); 
		//usleep(100000); 
		// This is too long because of the send_raw_frame overhead. 
		usleep(99910); 
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

					//
					recv_buf[n].data[0] = frame.data[0];
					recv_buf[n].data[1] = frame.data[1];
					recv_buf[n].data[2] = frame.data[2];
					recv_buf[n].data[3] = frame.data[3];
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


#define RECV_BUF_SIZE 5000 

void socketcan_isotp_receive( int target, char *dest, int *size ) 
{
   unsigned char msg[RECV_BUF_SIZE]; // baggy static reception buffer 
   int nbytes;

	// Setup the socket based on the target parameter 
	addr_isotp.can_family = AF_CAN;
	addr_isotp.can_ifindex = ifr.ifr_ifindex; 

	if( get_config_int("socketcan.primary_id") != -1 ) 
	{
		addr_isotp.can_addr.tp.tx_id = status_id + 1; 
		addr_isotp.can_addr.tp.rx_id = get_config_int("socketcan.primary_id") + 1; 
	}
	else 
	{
		if( target != -1 ) 
			addr_isotp.can_addr.tp.tx_id = target_ids[target] + 1;  // One above status
		else
			addr_isotp.can_addr.tp.tx_id = 0x200 + 1;  // There is no target 0. 

		addr_isotp.can_addr.tp.rx_id = status_id + 1;  
	}

	//fprintf(stderr, " Tx: %d Rx: %d \n", addr_isotp.can_addr.tp.tx_id, addr_isotp.can_addr.tp.rx_id); 
	if( bind(isotp_sock, (struct sockaddr *)&addr_isotp, sizeof(addr_can)) < 0) 
	{ 
		perror("bind isotp");
		return 1; 
	}

	FILE *output = NULL; 

	// Header, <data>, [Footer?] 
	do {
		nbytes = read(isotp_sock, msg, RECV_BUF_SIZE);
		if (nbytes > 0 && nbytes < RECV_BUF_SIZE)
		{
			// Debug ouput: 
			//for (int i=0; i < nbytes; i++)
			//	fprintf(stderr, "%02X ", msg[i]);

			if(output != NULL) 
				fwrite(msg, nbytes, 1, output);

			// Received a header sized datagram? 
			if( nbytes == sizeof(isotp_header_t) ) 
			{
				isotp_header_t hdr; 
				memcpy( &hdr, msg, sizeof(isotp_header_t)); 

				// If it has the magic number, it's likely the header
				if( hdr.magic_number = MAGIC_NUMBER ) 
				{
					fprintf(stderr, "\n Received Header \n");
					fprintf(stderr, " Data(%d) Size %d Frames %d File: %s ", hdr.data_type, 
							hdr.total_size, hdr.frame_count, hdr.filename); 
					output = fopen( hdr.filename, "w+");  // Open and blow out the file
				}
			}

		}
	} while (1);
}


