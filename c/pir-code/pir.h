#ifndef PIR_H
#define PIR_H

#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>

#include "../string-util/string-util.h"

/**
 * @brief Writes a PIR code to the character array from a wide character string
 * 
 * @param s The (wide) string where the PIR code is to be calculated from
 * @param c The character array (not wide) of the max. 5 digits of the PIR code
 */
void write_pir_code(const wchar_t * s, char c[5]);
#endif