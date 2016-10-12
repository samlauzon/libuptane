/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "CommonModule"
 * 	found in "CommonModule.asn1"
 */

#ifndef	_Hash_H_
#define	_Hash_H_


#include <asn_application.h>

/* Including external dependencies */
#include "HashFunction.h"
#include "BinaryData.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Hash */
typedef struct Hash {
	HashFunction_t	 function;
	BinaryData_t	 digest;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Hash_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Hash;

#ifdef __cplusplus
}
#endif

#endif	/* _Hash_H_ */
#include <asn_internal.h>
