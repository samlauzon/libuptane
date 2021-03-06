/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ApplicationModule"
 * 	found in "ApplicationModule.asn1"
 */

#ifndef	_ImageFile_H_
#define	_ImageFile_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Filename.h"
#include "Positive.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ImageFile */
typedef struct ImageFile {
	Filename_t	 filename;
	Positive_t	 numberOfBlocks;
	Positive_t	 blockSize;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ImageFile_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ImageFile;

#ifdef __cplusplus
}
#endif

#endif	/* _ImageFile_H_ */
#include <asn_internal.h>
