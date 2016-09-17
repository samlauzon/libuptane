//
//   web.h
//    implements the web interface for the "curl" wrapper
//

#ifndef __web_h
#define __web_h

void web_init( void *callback );
void web_fini( void ); 

void web_set_callback( void *callback ); 
void *web_get_callback( void ); 

int web_fetch( const char *url ); 

#endif //__web_h

