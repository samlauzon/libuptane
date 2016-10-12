/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "TargetsModule"
 * 	found in "TargetsModule.asn1"
 */

#ifndef	_DelegatedTargetsRoles_H_
#define	_DelegatedTargetsRoles_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct DelegatedTargetsRole;

/* DelegatedTargetsRoles */
typedef struct DelegatedTargetsRoles {
	A_SEQUENCE_OF(struct DelegatedTargetsRole) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} DelegatedTargetsRoles_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_DelegatedTargetsRoles;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "DelegatedTargetsRole.h"

#endif	/* _DelegatedTargetsRoles_H_ */
#include <asn_internal.h>