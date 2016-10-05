
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sysexits.h>
#include <errno.h>

#include "asn_application.h"
#include "asn_internal.h"

#include "Metadata.h"
#include "Signed.h" 
#include "UTCDateTime.h"
#include "TimestampMetadata.h"

#include "ber_decoder.h" 

int main(int argc, char **argv) 
{
	char *buf; 

	// Read the file and allocate dynamically 
	assert(argc == 2);
	char *filename = argv[1];
	FILE *f = fopen(filename, "r");
	if( f == NULL )
	{
		fprintf(stderr, "Cannot open file \"%s\" - Exiting.\n", filename);
		exit(-1);
	}

	fseek(f, 0, SEEK_END);
	int filesize = ftell(f);
	buf = (char *) malloc((size_t)filesize + 1); 
	memset(buf, 0, filesize + 1);
	rewind(f); 
	size_t size = fread(buf, 1, filesize, f);

	if(size == 0 || size > filesize ) {
		fprintf(stderr, "%s: Too large input\n", filename);
		exit(1);
	}

	// Made it this far.. 
	asn_dec_rval_t dv;
	Metadata_t *metadata; 

	dv = ber_decode(0, &asn_DEF_Metadata, (void **)&metadata, buf, size); 

	if(dv.code == RC_OK) {
		fprintf(stderr, "Decoded %d bytes of BER\n", dv.consumed); 
	}

	// Debug Print: 
	//   asn_fprint(stderr, &asn_DEF_Metadata, metadata); 

	Signed_t st = metadata->Signed;

	RoleType_t roletype; 
	memcpy( &roletype, &st.type, sizeof( RoleType_t )); 
	int role;
	asn_INTEGER2long(&roletype, &role); 


	Positive_t version; 
	memcpy( &version, &st.version, sizeof(Positive_t)); 
	int ver;
	asn_INTEGER2long(&version, &ver); 

	fprintf(stderr, "Role: %d \n", role);
	fprintf(stderr, "Expires: %s \n", (char *)st.expires.buf); 
	fprintf(stderr, "Version: %d \n", ver);

	SignedBody_t body = st.body;

	switch( body.present ) {
		case SignedBody_PR_timestampMetadata:
			fprintf(stderr, "Found Timestamp metadata.\n"); 
			break;
		case SignedBody_PR_snapshotMetadata: 
			fprintf(stderr, "Found Snapshot metadata.\n"); 
			break;
		case SignedBody_PR_targetsMetadata:
			fprintf(stderr, "Found Targets metadata.\n"); 
			break;
		case SignedBody_PR_rootMetadata:
			fprintf(stderr, "Found Root metadata.\n"); 
			break;
		default:
			fprintf(stderr, "Found No metadata?\n"); 
			break;
	}

	Signatures_t sigs = metadata->signatures; 

	fprintf(stderr, "Found %d signature(s)\n", sigs.list.count);

	Signature_t *sig; 
	sig = sigs.list.array[0]; 

	fprintf(stderr, "Key ID: %s \n", (char *)sig->keyid.buf); 
	int method; 
	asn_INTEGER2long(&sig->method, &method); 
	// Does this need a memcpy  or did it not blow out 'sig' ? 
	fprintf(stderr, "Method: %d\n", method);

	Hash_t hash = sig->hash;
	int func; 
	asn_INTEGER2long(&hash.function, &func);
	fprintf(stderr, "Hash function: %d\n", func); 

	BinaryData_t digest = hash.digest;
	switch(digest.present) { 
		case BinaryData_PR_hexString: 
			fprintf(stderr, "Hex string digest: %s \n", (char *)digest.choice.hexString.buf);
			break;

		case BinaryData_PR_bitString:
			fprintf(stderr, "is a bit string \n");
			break;

		// Default: 
	}
}


