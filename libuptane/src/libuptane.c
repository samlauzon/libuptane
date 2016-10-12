

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 

#include "libuptane.h"
#include "interfaces.h"

#include "sha256.h" 
#include "sha512.h"

#include "socketcan-wrapper.h" // remove me


char ncsha512[1024] = { 0 }; 
char ncsha256[1024] = { 0 }; 

 // To be removed/moved: 
void test_encodings() ;


void webdata_callback( const char *data ) 
{
	fprintf(stderr, "Received data from the web; \n");
	fprintf(stderr, data); 

	// Verified against http://hash.online-convert.com/sha512-generator
	int p = sha512(data, strlen(data), &ncsha512); 
	fprintf(stderr, "\n The SHA512 is: ", ncsha512);  
	for(int i = 0; i <= 63; i++) {
		fprintf(stderr, "%X", 0xFF & ncsha512[i]  ); 
	} 
	fprintf(stderr, "\n"); 

	// Sha 256? 

	struct sha256_state md; 
	sha256_init( &md ); 
	sha256_process( &md, data, strlen(data) ); 
	sha256_done( &md, ncsha256 ); 

	fprintf( stderr, " The SHA256 is: "); 
	for(int i = 0; i <= 31; i++) { 
		fprintf(stderr, "%X", 0xFF & ncsha256[i] ); 
	}
	fprintf(stderr, "\n\n"); 

	free( (void *) data); 	// was malloc'd in the wrapper. 
	//Probably bad. Add cbCleanup? 
}

void uptane_init( void )
{
	fprintf(stderr, "libuptane %d.%d.%d\n", 
			VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);


	init_config(); 

	web_init(webdata_callback); 
	// Uncomment and it'll output the webpage, sha512 and sha256 of the data
	//	web_fetch("https://www.samlauzon.com"); 

	init_can(); 

	// Broadcast some wakeup garbage
	send_raw_frame( 1, 1, 0xFF ); 
	send_raw_frame( 2, 2, 0xFF, 0xFF ); 
	send_raw_frame( 3, 3, 0xFF, 0xFF, 0xFF ); 
	send_raw_frame( 4, 4, 0xFF, 0xFF, 0xFF, 0xFF ); 
	send_raw_frame( 5, 5, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF ); 
	send_raw_frame( 6, 6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF ); 
	send_raw_frame( 7, 7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF ); 

	//send_raw_isotp(); 

	////////
	//  Test the ASN.1 Parsing
	//
	//  test_encodings(); 
}



#include "asn_application.h"
#include "asn_internal.h"

#include "Metadata.h"
#include "Signed.h"
#include "UTCDateTime.h"
#include "TimestampMetadata.h"

#include "ber_decoder.h"


void test_encodings() 
{
	char *buf; 
	char *filename = "directorTargetsMetadata.ber";
	FILE *f = fopen(filename, "rb");
	if( f == NULL )
	{
		fprintf(stderr, "Cannot open file \"%s\" - Exiting.\n", filename);
		return; 
	}

	fseek(f, 0, SEEK_END);
	int filesize = ftell(f);
	buf = (char *) malloc((size_t)filesize + 1);
	memset(buf, 0, filesize + 1);
	rewind(f);
	size_t size = fread(buf, 1, filesize, f);

	if(size == 0 || size > filesize ) 
	{
		fprintf(stderr, "%s: Too large input\n", filename);
		return;
	}
	// Lets get ugly and parse BER 
   // ASSUME metadata from the git-go.
		// That's signed, # sigs, signatures 
   // signed = roletype, timestamp, version, signedbody
		// signedbody = rootmetadata, targets, snapshot and timestamp 
	// .. ok. go.
	
	char *start = buf; 
	char *end = buf + size; 

	int slbc = 0;   // size byte length count 
	int sec_len = 0; 

	fprintf(stderr, "Starting:\n"); 	// VIM: BRACE MOVE PARSER
   while(0) { //buf != end) {
		if( *buf == 0x30 ) { buf++; 
			if( *buf & 0x80 ) { 
				slbc = *buf & 0x7F; sec_len = 0; 
				while(slbc--)  
					sec_len |= (*(++buf))<<( (slbc) * 8); 

			}
		}
	}
	fprintf(stderr, "Done.\n"); 

	
	struct sha256_state md; 
	sha256_init( &md ); 
	sha256_process( &md, start+5, 0x127 ); 
	sha256_done( &md, ncsha256 ); 

	fprintf( stderr, " The SHA256 is: "); 
	for(int i = 0; i <= 31; i++) { 
		fprintf(stderr, "%X", 0xFF & ncsha256[i] ); 
	}
	fprintf(stderr, "\n\n"); 


}


void uptane_finish( void ) 
{
	fini_can(); 

	web_fini(); 
	fini_config(); 
}

