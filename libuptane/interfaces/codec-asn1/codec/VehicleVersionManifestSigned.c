/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ApplicationModule"
 * 	found in "ApplicationModule.asn1"
 */

#include "VehicleVersionManifestSigned.h"

static asn_TYPE_member_t asn_MBR_VehicleVersionManifestSigned_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct VehicleVersionManifestSigned, vehicleIdentifier),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Identifier,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"vehicleIdentifier"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct VehicleVersionManifestSigned, primaryIdentifier),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Identifier,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"primaryIdentifier"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct VehicleVersionManifestSigned, numberOfECUVersionManifests),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Length,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"numberOfECUVersionManifests"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct VehicleVersionManifestSigned, ecuVersionManifests),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ECUVersionManifests,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ecuVersionManifests"
		},
};
static ber_tlv_tag_t asn_DEF_VehicleVersionManifestSigned_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_VehicleVersionManifestSigned_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* vehicleIdentifier at 21 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* primaryIdentifier at 23 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* numberOfECUVersionManifests at 24 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* ecuVersionManifests at 26 */
};
static asn_SEQUENCE_specifics_t asn_SPC_VehicleVersionManifestSigned_specs_1 = {
	sizeof(struct VehicleVersionManifestSigned),
	offsetof(struct VehicleVersionManifestSigned, _asn_ctx),
	asn_MAP_VehicleVersionManifestSigned_tag2el_1,
	4,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	3,	/* Start extensions */
	5	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_VehicleVersionManifestSigned = {
	"VehicleVersionManifestSigned",
	"VehicleVersionManifestSigned",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_VehicleVersionManifestSigned_tags_1,
	sizeof(asn_DEF_VehicleVersionManifestSigned_tags_1)
		/sizeof(asn_DEF_VehicleVersionManifestSigned_tags_1[0]), /* 1 */
	asn_DEF_VehicleVersionManifestSigned_tags_1,	/* Same as above */
	sizeof(asn_DEF_VehicleVersionManifestSigned_tags_1)
		/sizeof(asn_DEF_VehicleVersionManifestSigned_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_VehicleVersionManifestSigned_1,
	4,	/* Elements count */
	&asn_SPC_VehicleVersionManifestSigned_specs_1	/* Additional specs */
};

