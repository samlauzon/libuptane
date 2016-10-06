
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

int can_sock; 
int isotp_sock;


void init_socketcan( void ) 
{
	struct ifreq ifr;
	struct sockaddr_can addr;

	isotp_sock = socket(PF_CAN, SOCK_DGRAM, CAN_ISOTP);
	can_sock = socket(PF_CAN, SOCK_RAW, CAN_RAW); 

	if( (isotp_sock < 0) ) 
		fprintf(stderr, "Cannot open ISO-TP socket\n");

	if( (can_sock < 0) ) 
		fprintf(stderr, "Cannot open CAN socket\n"); 

	strcpy(ifr.ifr_name, get_config_string("socketcan.interface"));
	ifr.ifr_name[5] = '\0';

	ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);
	 if (!ifr.ifr_ifindex) {
		perror("if_nametoindex");
		return 1;
	}
	
	 addr.can_family = AF_CAN;
	 addr.can_ifindex = ifr.ifr_ifindex;

	 if (bind(can_sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		 perror("bind");
		 return 1;
	 }
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

