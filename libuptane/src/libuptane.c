
#include "libuptane.h"

#include <stdio.h>

void webdata_callback( void ) 
{
   fprintf(stderr, "Received data from the web.\n");
}

void uptane_init( void )
{
   fprintf(stderr, "I'm a library.\n");
   curl_init(webdata_callback); 
   curl_fetch("https://www.samlauzon.com"); 

}

