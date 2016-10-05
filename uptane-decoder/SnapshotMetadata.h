/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "SnapshotModule"
 * 	found in "SnapshotModule.asn1"
 */

#ifndef	_SnapshotMetadata_H_
#define	_SnapshotMetadata_H_


#include <asn_application.h>

/* Including external dependencies */
#include "StrictFilename.h"
#include "Version.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SnapshotMetadata */
typedef struct SnapshotMetadata {
	StrictFilename_t	 filename;
	Version_t	 version;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SnapshotMetadata_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SnapshotMetadata;

#ifdef __cplusplus
}
#endif

#endif	/* _SnapshotMetadata_H_ */
#include <asn_internal.h>