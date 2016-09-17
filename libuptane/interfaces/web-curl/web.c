//
//   web.c 
//    implements the web interface for the "curl" wrapper
//

#include <stdio.h>
#include <stdlib.h>
#include "curlwrapper.h"

#define debug_output(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__) // Debug output

//
// web_set_callback( void *callback )  
//
//    Sets the callback when the data is received from the remote interface 
// 

void web_set_callback( void *callback ) 
{
   curl_setcallback(callback); 
}

//
// void *web_get_callback()   
//    
//    Gets the currently set callback for remote data reception
//

void *web_get_callback( void ) 
{
   return curl_getcallback(); 
}

//
// web_init( void *callback ) 
// 
//    Initializes the web interface from the main library 
//

void web_init( void *callback ) 
{
   curl_init(callback); 
}

//
// web_fini()
//
//   Cleans up the web interface          
// 

void web_fini( void ) 
{
   curl_fini();
}


//
// int web_fetch( url ) 
//
//   Fetch a URL and call the callback when complete
//   TODO: Fix error codes

int web_fetch( const char *url ) 
{
   return (int)curl_fetch(url); 
}



