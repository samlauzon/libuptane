
#include "config.h"

 // Todo: maybe a lookup table? 

void init_config() 
{
}

void fini_config()
{
}

char *get_config_string( const char *val ) 
{
	if( strcmp(val, "socketcan.interface") == 0 ) 
		return "can0"; 
}

int get_config_int( const char *val ) 
{
	if( strcmp(val, "zero") == 0 )
		return 0;
}



