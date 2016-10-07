

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 

#include "libuptane.h"
#include "interfaces.h"

#include "sha256.h" 
#include "sha512.h"

#include "socketcan-wrapper.h" // remove me


char ncsha512[1024] = { 0 }; 
char ncsha256[1024] = { 0 }; 

void webdata_callback( const char *data ) 
{
	fprintf(stderr, "Received data from the web; \n");
	fprintf(stderr, data); 

	// Verified against http://hash.online-convert.com/sha512-generator
	int p = sha512(data, strlen(data), &ncsha512); 
	fprintf(stderr, "\n The SHA512 is: ", ncsha512);  
	for(int i = 0; i <= 63; i++) {
		fprintf(stderr, "%X", 0xFF & ncsha512[i]  ); 
	} 
	fprintf(stderr, "\n"); 

	// Sha 256? 

	struct sha256_state md; 
	sha256_init( &md ); 
	sha256_process( &md, data, strlen(data) ); 
	sha256_done( &md, ncsha256 ); 

	fprintf( stderr, " The SHA256 is: "); 
	for(int i = 0; i <= 31; i++) { 
		fprintf(stderr, "%X", 0xFF & ncsha256[i] ); 
	}
	fprintf(stderr, "\n\n"); 

	free( (void *) data); 	// was malloc'd in the wrapper. 
	//Probably bad. Add cbCleanup? 
}

void uptane_init( void )
{
	fprintf(stderr, "libuptane %d.%d.%d\n", 
			VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);


	init_config(); 

	web_init(webdata_callback); 
	//	web_fetch("https://www.samlauzon.com"); 

	init_can(); 
	send_raw_frame( 1, 1, 0xFF ); 
	send_raw_frame( 2, 2, 0xFF, 0xFF ); 
	send_raw_frame( 3, 3, 0xFF, 0xFF, 0xFF ); 
	send_raw_frame( 4, 4, 0xFF, 0xFF, 0xFF, 0xFF ); 
	send_raw_frame( 5, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF ); 
	send_raw_frame( 6, 6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF ); 
	send_raw_frame( 7, 7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF ); 

	send_raw_isotp(); 

}


void uptane_finish( void ) 
{
	web_fini(); 
	fini_config(); 
}

