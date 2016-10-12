/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "CommonModule"
 * 	found in "CommonModule.asn1"
 */

#ifndef	_Path_H_
#define	_Path_H_


#include <asn_application.h>

/* Including external dependencies */
#include <VisibleString.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Path */
typedef VisibleString_t	 Path_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Path;
asn_struct_free_f Path_free;
asn_struct_print_f Path_print;
asn_constr_check_f Path_constraint;
ber_type_decoder_f Path_decode_ber;
der_type_encoder_f Path_encode_der;
xer_type_decoder_f Path_decode_xer;
xer_type_encoder_f Path_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _Path_H_ */
#include <asn_internal.h>
