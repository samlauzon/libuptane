/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ApplicationModule"
 * 	found in "ApplicationModule.asn1"
 */

#ifndef	_ECUVersionManifests_H_
#define	_ECUVersionManifests_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ECUVersionManifest;

/* ECUVersionManifests */
typedef struct ECUVersionManifests {
	A_SEQUENCE_OF(struct ECUVersionManifest) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ECUVersionManifests_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ECUVersionManifests;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "ECUVersionManifest.h"

#endif	/* _ECUVersionManifests_H_ */
#include <asn_internal.h>