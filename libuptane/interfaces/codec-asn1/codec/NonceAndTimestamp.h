/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "TimeServerModule"
 * 	found in "TimeServerModule.asn1"
 */

#ifndef	_NonceAndTimestamp_H_
#define	_NonceAndTimestamp_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Nonce.h"
#include "UTCDateTime.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* NonceAndTimestamp */
typedef struct NonceAndTimestamp {
	Nonce_t	 nonce;
	UTCDateTime_t	 timestamp;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NonceAndTimestamp_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_NonceAndTimestamp;

#ifdef __cplusplus
}
#endif

#endif	/* _NonceAndTimestamp_H_ */
#include <asn_internal.h>
