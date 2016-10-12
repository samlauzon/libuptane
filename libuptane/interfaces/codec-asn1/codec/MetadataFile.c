/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "ApplicationModule"
 * 	found in "ApplicationModule.asn1"
 */

#include "MetadataFile.h"

static asn_TYPE_member_t asn_MBR_MetadataFile_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MetadataFile, broadcastGUID),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"broadcastGUID"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MetadataFile, fileNumber),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Positive,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"fileNumber"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MetadataFile, filename),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Filename,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"filename"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MetadataFile, metadata),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Metadata,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"metadata"
		},
};
static ber_tlv_tag_t asn_DEF_MetadataFile_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_MetadataFile_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* broadcastGUID at 44 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* fileNumber at 46 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* filename at 48 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* metadata at 51 */
};
static asn_SEQUENCE_specifics_t asn_SPC_MetadataFile_specs_1 = {
	sizeof(struct MetadataFile),
	offsetof(struct MetadataFile, _asn_ctx),
	asn_MAP_MetadataFile_tag2el_1,
	4,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_MetadataFile = {
	"MetadataFile",
	"MetadataFile",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_MetadataFile_tags_1,
	sizeof(asn_DEF_MetadataFile_tags_1)
		/sizeof(asn_DEF_MetadataFile_tags_1[0]), /* 1 */
	asn_DEF_MetadataFile_tags_1,	/* Same as above */
	sizeof(asn_DEF_MetadataFile_tags_1)
		/sizeof(asn_DEF_MetadataFile_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_MetadataFile_1,
	4,	/* Elements count */
	&asn_SPC_MetadataFile_specs_1	/* Additional specs */
};

