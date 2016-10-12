/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "MetadataModule"
 * 	found in "MetadataModule.asn1"
 */

#ifndef	_Signed_H_
#define	_Signed_H_


#include <asn_application.h>

/* Including external dependencies */
#include "RoleType.h"
#include "UTCDateTime.h"
#include "Positive.h"
#include "SignedBody.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Signed */
typedef struct Signed {
	RoleType_t	 type;
	UTCDateTime_t	 expires;
	Positive_t	 version;
	SignedBody_t	 body;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Signed_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Signed;

#ifdef __cplusplus
}
#endif

#endif	/* _Signed_H_ */
#include <asn_internal.h>
