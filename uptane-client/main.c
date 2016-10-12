
#include "libuptane.h"  // 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) 
{
   fprintf(stderr, "[uptane-client] Calling uptane_init: "); 
   uptane_init( ); // libUptane uptane_init 
   fprintf(stderr, "\n"); 

	sleep(2); 
	fprintf(stderr, " -- Press Enter to leave the client -- \n"); 
	while( 1 ) 
	{
		getc(stdin); 
		break; 
	}
	fprintf(stderr, "[uptane-client] Calling uptane_finish: \n"); 
	uptane_finish(); 
	fprintf(stderr, "[uptane-client] Now exiting..\n"); 
	sleep(2);
   
   return 0;
}
