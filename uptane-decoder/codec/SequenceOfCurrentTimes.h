/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "TimeServerModule"
 * 	found in "TimeServerModule.asn1"
 */

#ifndef	_SequenceOfCurrentTimes_H_
#define	_SequenceOfCurrentTimes_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Length.h"
#include "CurrentTimes.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SequenceOfCurrentTimes */
typedef struct SequenceOfCurrentTimes {
	Length_t	 numberOfCurrentTimes;
	CurrentTimes_t	 currentTimes;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceOfCurrentTimes_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SequenceOfCurrentTimes;

#ifdef __cplusplus
}
#endif

#endif	/* _SequenceOfCurrentTimes_H_ */
#include <asn_internal.h>
