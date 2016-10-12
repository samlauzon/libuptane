/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "TargetsModule"
 * 	found in "TargetsModule.asn1"
 */

#ifndef	_EncryptedSymmetricKey_H_
#define	_EncryptedSymmetricKey_H_


#include <asn_application.h>

/* Including external dependencies */
#include "EncryptedSymmetricKeyType.h"
#include "BinaryData.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* EncryptedSymmetricKey */
typedef struct EncryptedSymmetricKey {
	EncryptedSymmetricKeyType_t	 encryptedSymmetricKeyType;
	BinaryData_t	 encryptedSymmetricKeyValue;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} EncryptedSymmetricKey_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_EncryptedSymmetricKey;

#ifdef __cplusplus
}
#endif

#endif	/* _EncryptedSymmetricKey_H_ */
#include <asn_internal.h>
