/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ApplicationModule"
 * 	found in "ApplicationModule.asn1"
 */

#ifndef	_MetadataBroadcast_H_
#define	_MetadataBroadcast_H_


#include <asn_application.h>

/* Including external dependencies */
#include <INTEGER.h>
#include "Positive.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MetadataBroadcast */
typedef struct MetadataBroadcast {
	INTEGER_t	 broadcastGUID;
	Positive_t	 numberOfMetadataFiles;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MetadataBroadcast_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MetadataBroadcast;

#ifdef __cplusplus
}
#endif

#endif	/* _MetadataBroadcast_H_ */
#include <asn_internal.h>
