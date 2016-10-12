/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "MetadataModule"
 * 	found in "MetadataModule.asn1"
 */

#include "SignedBody.h"

static asn_TYPE_member_t asn_MBR_SignedBody_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SignedBody, choice.rootMetadata),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RootMetadata,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"rootMetadata"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SignedBody, choice.targetsMetadata),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TargetsMetadata,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"targetsMetadata"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SignedBody, choice.snapshotMetadata),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SnapshotMetadata,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"snapshotMetadata"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SignedBody, choice.timestampMetadata),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TimestampMetadata,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"timestampMetadata"
		},
};
static asn_TYPE_tag2member_t asn_MAP_SignedBody_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* rootMetadata at 28 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* targetsMetadata at 29 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* snapshotMetadata at 30 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* timestampMetadata at 32 */
};
static asn_CHOICE_specifics_t asn_SPC_SignedBody_specs_1 = {
	sizeof(struct SignedBody),
	offsetof(struct SignedBody, _asn_ctx),
	offsetof(struct SignedBody, present),
	sizeof(((struct SignedBody *)0)->present),
	asn_MAP_SignedBody_tag2el_1,
	4,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_SignedBody = {
	"SignedBody",
	"SignedBody",
	CHOICE_free,
	CHOICE_print,
	CHOICE_constraint,
	CHOICE_decode_ber,
	CHOICE_encode_der,
	CHOICE_decode_xer,
	CHOICE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	CHOICE_outmost_tag,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	0,	/* No PER visible constraints */
	asn_MBR_SignedBody_1,
	4,	/* Elements count */
	&asn_SPC_SignedBody_specs_1	/* Additional specs */
};
