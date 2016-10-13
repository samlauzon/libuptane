

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 

#include "libuptane.h"
#include "interfaces.h"

#include "sha256.h" 
#include "sha512.h"

#include "asn_application.h"
#include "asn_internal.h"

#include "Metadata.h"
#include "Signed.h"
#include "UTCDateTime.h"
#include "TimestampMetadata.h"

#include "ber_decoder.h"


char hexDigit(unsigned n)
{
	if (n < 10) {
		return n + '0';
	} else {
		return (n - 10) + 'a';
	}
}

void charToHex(char c, char hex[2])
{
	hex[0] = hexDigit(c / 0x10);
	hex[1] = hexDigit(c % 0x10);
}

char hashstring[65]; 
char *hs; 
int sec_len;

void verify_metadata( char * filename )
{
	char *buf; 
	int i = 0; 
	
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

	/////////////
	// Parse some things 
	asn_dec_rval_t dv;
	Metadata_t *metadata = (Metadata_t *)malloc( sizeof(Metadata_t));  
	// This above metadata structure had to be malloc'd to work here, after it was previously not malloc'd.
	//  There's likely a leak somewhere.

	dv = ber_decode(0, &asn_DEF_Metadata, (void **)&metadata, buf, size); 

	if(dv.code == RC_OK) {
		fprintf(stderr, "Decoded %d bytes of BER\n", dv.consumed); 
	}

	/////
	// Manual BER parse to find the length of the Signatures section 
	// THIS IS BAD. Probably; 
	//fprintf(stderr, "%x size bytes\n", *(buf+5)^0x80);
	sec_len = 0; 
	for(i = 0; i <= ((*(buf+5)^0x80)-1); i++) 
	{
		// fprintf(stderr, "%d: %x ", i, *(buf+6+i)); 
		sec_len |= (*(buf+6+i))<<( ((*(buf+5)^0x80)-(i+1)) * 8); 
	}
	sec_len += 4;
	//fprintf(stderr, "I think the size of signatures is... %d \n", sec_len); 
	
	// Debug Print: 
	//   asn_fprint(stderr, &asn_DEF_Metadata, metadata); 

	Signed_t st = metadata->Signed;

	RoleType_t roletype; 
	memcpy( &roletype, &st.type, sizeof( RoleType_t )); 
	int role;
	asn_INTEGER2long(&roletype, &role);  // 0 root | 1 targets | 2 snapshot | 3 timestamp

	switch(role) { 
		case 0: fprintf(stderr, "root"); break;
		case 1: fprintf(stderr, "targets"); break;
		case 2: fprintf(stderr, "snapshots"); break;
		case 3: fprintf(stderr, "timestamp"); break; 
		default: fprintf(stderr, "broken"); break; 

	}
	fprintf(stderr, " Role detected\n");

	UTCDateTime_t expires; 
	memcpy( &expires, &st.expires, sizeof( UTCDateTime_t )); 
	long expiry;
	asn_INTEGER2long(&expires, &expiry); 
	fprintf(stderr, "Expires %d\n", expiry);

	Signatures_t sigs = metadata->signatures; 
	fprintf(stderr, "Found %d signature(s)\n", sigs.list.count);

	Hash_t hash = sigs.list.array[0]->hash;	
	int func; 
	asn_INTEGER2long(&hash.function, &func);
	fprintf(stderr, "Hash function: %d\n", func); 

	BinaryData_t digest = hash.digest;
	fprintf(stderr, "Hex string digest: %s \n", (char *)digest.choice.hexString.buf);
	// Accurate Hash: 
	struct sha256_state md; 
	char filehash[32]; 
	hs = hashstring; 


	sha256_init( &md ); 
	sha256_process( &md, buf+0x04, sec_len ); 
	sha256_done( &md, filehash ); 

	char nv[2]; 
	for(i = 0; i <= 31; i++) { 
		//fprintf(stderr, "%x", 0xFF & filehash[i] ); 
		charToHex(0xFF&filehash[i], nv); 
      *(hs++) = nv[0]; *(hs++) = nv[1];  
	}
	*hs='\0'; // Not really required due to strncmp  

	// Compare 
	if(strncmp (hashstring, digest.choice.hexString.buf, 64) == 0 ) 
		fprintf(stderr, "WE HAVE A WINNER!!!!\n"); 
	else
		fprintf(stderr, "Whatchu talkin 'bout, Willis?\n"); 
}


