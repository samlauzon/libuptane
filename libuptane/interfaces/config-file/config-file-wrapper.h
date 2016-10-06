
#if __config_file_wrapper_h
#define __config_file_wrapper_h

void configfile_wrapper_init( void );
int get_configfile_wrapper_int(const char *val); 
char *get_configfile_string(const char *val);

void free_configfile_list();

#endif //__config_file_wrapper_h


