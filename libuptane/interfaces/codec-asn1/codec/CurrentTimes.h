/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "TimeServerModule"
 * 	found in "TimeServerModule.asn1"
 */

#ifndef	_CurrentTimes_H_
#define	_CurrentTimes_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct CurrentTime;

/* CurrentTimes */
typedef struct CurrentTimes {
	A_SEQUENCE_OF(struct CurrentTime) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CurrentTimes_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CurrentTimes;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "CurrentTime.h"

#endif	/* _CurrentTimes_H_ */
#include <asn_internal.h>
