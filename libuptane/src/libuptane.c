

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 

#include "libuptane.h"
#include "interfaces.h"

#include "socketcan-wrapper.h" // remove me

#include "metadata.h"


void webdata_callback( const char *data ) 
{
	fprintf(stderr, "Received data from the web; \n");
	fprintf(stderr, data); 

	free( (void *) data); 	// was malloc'd in the wrapper. 
}

void uptane_init( void )
{
	fprintf(stderr, "libuptane %d.%d.%d\n", 
			VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);

	init_config(); 
	web_init(webdata_callback); 
	init_can(); 

	// Test? 
	//verify_metadata("directorTargetsMetadata.ber"); 
}



void uptane_finish( void ) 
{
	web_fini(); 
	fini_can(); 
	fini_config(); 
}

