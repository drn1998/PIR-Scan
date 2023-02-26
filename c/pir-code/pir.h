#ifndef PIR_H
#define PIR_H

#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>

#include "../string-util/string-util.h"

#define PIR_CODE_LENGTH 5

typedef struct {
    char pir[PIR_CODE_LENGTH];
    size_t pos;
} pir_t;

/**
 * @brief Initializes a pir_t object so that the position is set to zero and every digit is '0'
 * 
 * @param pir The pir_t object to be initialized
 */
void pir_code_init(pir_t * pir);

/**
 * @brief Writes a PIR code to the character array from a wide character string
 * 
 * @param ws The (wide) string where the PIR code is to be calculated from
 * @param pir The pir_t object where the resulting PIR code is written to
 */
void pir_code_write(const wchar_t * ws, pir_t * pir);
#endif