

#include "config.h"
#include "config-file-wrapper.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct config_node { 
	char *parameter;
	char *value;

	struct config_node *next; 
} cnode; 

cnode *config = NULL; 
int i = 0;

void push(char *param, char *value) {
	cnode *current = config;
	while(current->next != NULL) 
	{
		current = current->next;
	}
	current->next = malloc(sizeof(cnode));

	current->parameter = malloc( strlen(param) + 1 );
   memset( current->parameter, '\0', strlen(param) + 1); 
	strncpy(current->parameter, param, strlen(param));
	
	current->value = malloc( strlen(value) + 1 );
   memset( current->value, '\0', strlen(value) + 1); 
	strncpy(current->value, value, strlen(value));

	current->next->next = NULL;

}

// Debugging 
void print_list() 
{
	cnode* current = config;

	while (current->next != NULL) 
	{
		if( current->parameter && current->value ) 
		{ 
			printf("%s :: %s\n", current->parameter, current->value);
		}
		current = current->next;
	}
}

char *get_config_string( const char *val ) 
{
	cnode* current = config;

	while (current != NULL) {
		if( current->parameter && current->value ) { 
			if( strcmp(val, current->parameter) == 0) {
				return (current->value); 
			}
		}

		current = current->next;
	}
	return NULL; 
}

int get_config_int( const char *val ) 
{
	cnode* current = config;

	while (current != NULL) {
		if( current->parameter && current->value ) { 
			if( strcmp(val, current->parameter) == 0) {
				//fprintf(stderr, "get config int: Found %s with val of %s \n", current->parameter, current->value); 
				return atoi(current->value); 
			}
		}

		current = current->next;
	}
	return -1; 
}


void configfile_wrapper_init( void ) 
{
	FILE *fp;
	int filesize = 0;

	if( !(fp = fopen("config.ini", "r")) )
	{
		fprintf(stderr, "Cannot open config.ini"); 
		return;
	}

	config = malloc(sizeof(cnode));
	//fprintf(stderr, "Stack at 0x%x\n", config);
	config->parameter = "param";
	config->value = "value";
	config->next = NULL; 


	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	rewind(fp); 

	fprintf(stderr, "[config-file] config.ini is %d bytes.\n", filesize); 

	char *buf;
	if( (buf = (char *)malloc((size_t)filesize)) == NULL ) 
	{
		fprintf(stderr, "Cannot allocate %d bytes to cache config.ini", filesize);
		return; 
	}
	//fprintf(stderr, "File 0x%x\n", buf);

	fread(buf, filesize, 1, fp); 
	// Parser rules:
	//  value name = something
	//   if there's a hash or a semicolon - stop processing the line. 
	//
	//    if something has a quote -- Its a string. 
	//    if something has a 0x -- Its a hex val.
	//    all else is an int. 
	//     -- No other types are accepted -- 

	char *line;
	int i = 0; 

	char *tmp; 
	char *param, *value; 

	for( line = strtok(buf, "\n"); line; line = strtok(NULL, "\n") )
	{
		tmp = strdup(line); 

		param = (char *) malloc(strlen(tmp));
		memset(param, 0, strlen(tmp));

		value = (char *) malloc(strlen(tmp)); 
		memset(value, 0, strlen(tmp));

		value = strchr(tmp, '=');

		if( value ) 
		{ 
			//strncpy( param, tmp, strlen(tmp) - strlen(value)); 
			//memcpy( param, tmp, strlen(tmp) - strlen(value)); 
			//fprintf(stderr, " param: \"%s\"", param); 
			//fprintf(stderr, " value: \"%s\" \n", value+1);
			sscanf(tmp, "%s = %s", param, value); 
			push( param, value ); 
		}

		i++;
		//fprintf(stderr, "attempting to free 0x%x\n", tmp);
		free(tmp); 
		//fprintf(stderr, "attempting to free 0x%x\n", param);
		free(param);
	}

	//fprintf(stderr, "Config values: \n");
	//print_list();
}




