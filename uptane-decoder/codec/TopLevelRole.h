/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "RootModule"
 * 	found in "RootModule.asn1"
 */

#ifndef	_TopLevelRole_H_
#define	_TopLevelRole_H_


#include <asn_application.h>

/* Including external dependencies */
#include "RoleType.h"
#include "Length.h"
#include "Keyids.h"
#include "Threshold.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct URLs;

/* TopLevelRole */
typedef struct TopLevelRole {
	RoleType_t	 role;
	Length_t	*numberOfURLs	/* OPTIONAL */;
	struct URLs	*urls	/* OPTIONAL */;
	Length_t	 numberOfKeyids;
	Keyids_t	 keyids;
	Threshold_t	 threshold;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TopLevelRole_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TopLevelRole;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "URLs.h"

#endif	/* _TopLevelRole_H_ */
#include <asn_internal.h>
