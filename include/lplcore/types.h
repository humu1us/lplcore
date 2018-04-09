#ifndef LUPULUS_TYPE_H
#define LUPULUS_TYPE_H

 /*
 * TODO: add missing types:
 * category and date/time
 */

enum _lpl_type
{
    lpl_no_type,
    lpl_char,
    lpl_uchar,
    lpl_string,
    lpl_int8,
    lpl_int16,
    lpl_int32,
    lpl_int64,
    lpl_uint8,
    lpl_uint16,
    lpl_uint32,
    lpl_uint64,
    lpl_float32,
    lpl_float64,
    lpl_bool
};

typedef enum _lpl_type lpl_type_t;

#endif
