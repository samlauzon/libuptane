
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

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

	 struct canfd_frame f;
	 f.can_id = 0x123;
	 f.len = 8;
	 f.data[0] = 0x12;
	 f.data[1] = 0x34;
	 f.data[2] = 0x56;
	 f.data[3] = 0x78;
	 f.data[4] = 0x89;
	 f.data[5] = 0x61;
	 f.data[6] = 0x31;
	 f.data[7] = 0x21;

	 write(can_sock, &f, CAN_MTU);

}

