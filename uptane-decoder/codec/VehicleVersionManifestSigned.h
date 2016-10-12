/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ApplicationModule"
 * 	found in "ApplicationModule.asn1"
 */

#ifndef	_VehicleVersionManifestSigned_H_
#define	_VehicleVersionManifestSigned_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Identifier.h"
#include "Length.h"
#include "ECUVersionManifests.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* VehicleVersionManifestSigned */
typedef struct VehicleVersionManifestSigned {
	Identifier_t	 vehicleIdentifier;
	Identifier_t	 primaryIdentifier;
	Length_t	 numberOfECUVersionManifests;
	ECUVersionManifests_t	 ecuVersionManifests;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} VehicleVersionManifestSigned_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_VehicleVersionManifestSigned;

#ifdef __cplusplus
}
#endif

#endif	/* _VehicleVersionManifestSigned_H_ */
#include <asn_internal.h>
