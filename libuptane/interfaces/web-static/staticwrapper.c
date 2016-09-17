
#include <stdio.h>
#include <stdlib.h> 
#include "staticwrapper.h" 
#define debug_output(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__) // Debug output

void *data_callback = NULL; 
void static_init( void *callback ) 
{
   data_callback = callback; 
   debug_output("Called static_init\n");
}

void static_fini( void ) 
{
   debug_output("Called static_fini\n");
} 

void static_set_callback( void *callback ) 
{
   data_callback = callback;
   debug_output("Called static_set_callback\n");
}

void *static_get_callback(void)
{
   debug_output("Called static_get_callback\n");
   return data_callback;
}

int static_fetch( const char *url )
{
   ((void (*)(void)) data_callback)(); // Call the callback in main application
   return 0;
}

