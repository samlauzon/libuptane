/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "BootloaderModule"
 * 	found in "BootloaderModule.asn1"
 */

#ifndef	_VersionReport_H_
#define	_VersionReport_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Nonce.h"
#include "ECUVersionManifest.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* VersionReport */
typedef struct VersionReport {
	Nonce_t	 nonceForTimeServer;
	ECUVersionManifest_t	 ecuVersionManifest;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} VersionReport_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_VersionReport;

#ifdef __cplusplus
}
#endif

#endif	/* _VersionReport_H_ */
#include <asn_internal.h>