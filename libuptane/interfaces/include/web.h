//
//   web.h
//    All web wrappers must implement these functions
//
//

#ifndef __web_h
#define __web_h

void web_init( void *callback );
void web_fini( void ); 

void web_set_callback( void *callback ); 
void *web_get_callback( void ); 

int web_fetch( const char *url ); 

#endif //__web_h

