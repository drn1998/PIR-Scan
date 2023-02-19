#ifndef PIR_H
#define PIR_H

#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>

void write_pir_code(const wchar_t * s, char c[5]);
int wcspfx(const wchar_t *pre, const wchar_t *str);

#endif