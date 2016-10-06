
#include "config.h"
#include "config-file-wrapper.h"

void init_config() 
{
	configfile_wrapper_init();
}

int get_config_int(const char *val) 
{
	return get_configfile_wrapper_int(val);
}

char *get_config_string(const char *val)
{
	return get_configfile_wrapper_string(val);
}

void fini_config( void ) 
{
	free_configfile_list();
}

