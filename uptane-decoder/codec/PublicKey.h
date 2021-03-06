/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "CommonModule"
 * 	found in "CommonModule.asn1"
 */

#ifndef	_PublicKey_H_
#define	_PublicKey_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Keyid.h"
#include "PublicKeyType.h"
#include "BinaryData.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PublicKey */
typedef struct PublicKey {
	Keyid_t	 publicKeyid;
	PublicKeyType_t	 publicKeyType;
	BinaryData_t	 publicKeyValue;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PublicKey_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PublicKey;

#ifdef __cplusplus
}
#endif

#endif	/* _PublicKey_H_ */
#include <asn_internal.h>
