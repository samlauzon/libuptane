

#include "can.h"
#include "socketcan-wrapper.h"

void init_can( void ) 
{
	init_socketcan(); 

}

void fini_can( void ) 
{
	fini_socketcan();
}

