/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ApplicationModule"
 * 	found in "ApplicationModule.asn1"
 */

#ifndef	_MetadataFile_H_
#define	_MetadataFile_H_


#include <asn_application.h>

/* Including external dependencies */
#include <INTEGER.h>
#include "Positive.h"
#include "Filename.h"
#include "Metadata.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MetadataFile */
typedef struct MetadataFile {
	INTEGER_t	 broadcastGUID;
	Positive_t	 fileNumber;
	Filename_t	 filename;
	Metadata_t	 metadata;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MetadataFile_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MetadataFile;

#ifdef __cplusplus
}
#endif

#endif	/* _MetadataFile_H_ */
#include <asn_internal.h>