
#include "libuptane.h"  // 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) 
{
   fprintf(stderr, "[uptane-client] Calling uptane_init: "); 
   uptane_init( ); // libUptane uptane_init 
   fprintf(stderr, "\n"); 

   sleep(10);
   
   return 0;
}
