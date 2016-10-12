/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "TrustPinningModule"
 * 	found in "TrustPinningModule.asn1"
 */

#ifndef	_RepositoryDelegations_H_
#define	_RepositoryDelegations_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct RepositoryDelegation;

/* RepositoryDelegations */
typedef struct RepositoryDelegations {
	A_SEQUENCE_OF(struct RepositoryDelegation) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RepositoryDelegations_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RepositoryDelegations;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "RepositoryDelegation.h"

#endif	/* _RepositoryDelegations_H_ */
#include <asn_internal.h>
