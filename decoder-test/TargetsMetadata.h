/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "TargetsModule"
 * 	found in "TargetsModule.asn1"
 */

#ifndef	_TargetsMetadata_H_
#define	_TargetsMetadata_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Targets.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct TargetsDelegations;

/* TargetsMetadata */
typedef struct TargetsMetadata {
	Targets_t	 targets;
	struct TargetsDelegations	*delegations	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TargetsMetadata_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TargetsMetadata;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "TargetsDelegations.h"

#endif	/* _TargetsMetadata_H_ */
#include <asn_internal.h>
