

#ifndef __curlwrapper_h
#define __curlwrapper_h

#include <stdint.h> 

void curl_init( void* fn ); 
size_t fetch_callback(void *contents, size_t size, size_t nmemb, void *userp);
void curl_setcallback( void *fn );
void *curl_getcallback( void );
uint8_t curl_fetch( const char *url );
void curl_fini( void );


#endif //__curlwrapper_h


