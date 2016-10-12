/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "CommonModule"
 * 	found in "CommonModule.asn1"
 */

#ifndef	_UTCDateTime_H_
#define	_UTCDateTime_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Positive.h"

#ifdef __cplusplus
extern "C" {
#endif

/* UTCDateTime */
typedef Positive_t	 UTCDateTime_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UTCDateTime;
asn_struct_free_f UTCDateTime_free;
asn_struct_print_f UTCDateTime_print;
asn_constr_check_f UTCDateTime_constraint;
ber_type_decoder_f UTCDateTime_decode_ber;
der_type_encoder_f UTCDateTime_encode_der;
xer_type_decoder_f UTCDateTime_decode_xer;
xer_type_encoder_f UTCDateTime_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _UTCDateTime_H_ */
#include <asn_internal.h>
