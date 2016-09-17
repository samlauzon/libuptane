
#include "libuptane.h"
#include "interfaces.h"

#include <stdio.h>

void webdata_callback( void ) 
{
   fprintf(stderr, "Received data from the web.\n");
}

void uptane_init( void )
{
   fprintf(stderr, "I'm a library.\n");
   web_init(webdata_callback); 
   web_fetch("https://www.samlauzon.com"); 
   web_fini(); 
}

