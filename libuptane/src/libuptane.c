

#include <stdio.h>
#include <stdlib.h>

#include "libuptane.h"
#include "interfaces.h"

void webdata_callback( const char *data ) 
{
	fprintf(stderr, data); 
	free( (void *) data); // was malloc'd in the wrapper.
	fprintf(stderr, "Received data from the web.\n");
}

void uptane_init( void )
{
	fprintf(stderr, "libuptane %d.%d.%d - Copyright 2016 (c) Sam Lauzon, University of Michigan", 
			VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);

	web_init(webdata_callback); 
	web_fetch("https://www.samlauzon.com"); 
	web_fini(); 
}

