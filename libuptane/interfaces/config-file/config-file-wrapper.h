
#if __config_file_wrapper_h
#define __config_file_wrapper_h

void configfile_wrapper_init( void );
int get_config_int(const char *val); 
char *get_config_string(const char *val);

void free_list();

#endif //__config_file_wrapper_h


