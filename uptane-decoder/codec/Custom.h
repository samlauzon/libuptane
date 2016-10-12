/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "TargetsModule"
 * 	found in "TargetsModule.asn1"
 */

#ifndef	_Custom_H_
#define	_Custom_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Identifier.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct Target;
struct EncryptedSymmetricKey;

/* Custom */
typedef struct Custom {
	Identifier_t	 ecuIdentifier;
	struct Target	*encryptedTarget	/* OPTIONAL */;
	struct EncryptedSymmetricKey	*encryptedSymmetricKey	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Custom_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Custom;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "Target.h"
#include "EncryptedSymmetricKey.h"

#endif	/* _Custom_H_ */
#include <asn_internal.h>
