

#include <stdio.h>
#include <stdlib.h>

#include "libuptane.h"
#include "interfaces.h"

#include "sha512.h"


char ncsha512[1024] = { 0 }; 


void webdata_callback( const char *data ) 
{
	fprintf(stderr, "Received data from the web; \n");
	fprintf(stderr, data); 
	
	// Verified against http://hash.online-convert.com/sha512-generator
	int p = sha512(data, strlen(data), &ncsha512); 
	fprintf(stderr, "\n The sha512 of the data above is: ", ncsha512);  
	for(int i = 0; i <= 63; i++) {
      fprintf(stderr, "%X", 0xFF & ncsha512[i]  ); 
   } 
	fprintf(stderr, "\n\n"); 

	free( (void *) data); // was malloc'd in the wrapper.
}

void uptane_init( void )
{
	fprintf(stderr, "libuptane %d.%d.%d - Copyright 2016 (c) Sam Lauzon, University of Michigan", 
			VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);

	web_init(webdata_callback); 
	web_fetch("https://www.samlauzon.com"); 
	web_fini(); 

}

