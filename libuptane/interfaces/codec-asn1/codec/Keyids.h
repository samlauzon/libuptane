/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "CommonModule"
 * 	found in "CommonModule.asn1"
 */

#ifndef	_Keyids_H_
#define	_Keyids_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Keyid.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Keyids */
typedef struct Keyids {
	A_SEQUENCE_OF(Keyid_t) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Keyids_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Keyids;

#ifdef __cplusplus
}
#endif

#endif	/* _Keyids_H_ */
#include <asn_internal.h>
