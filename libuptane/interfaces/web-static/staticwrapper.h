//
//   staticwrapper.h
//

#ifndef __staticwrapper_h
#define __staticwrapper_h

void static_init( void *callback );
void static_fini( void ); 

void static_set_callback( void *callback ); 
void *static_get_callback( void ); 

int static_fetch( const char *url ); 

#endif //__staticwrapper_h
