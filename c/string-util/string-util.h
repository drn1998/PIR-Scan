#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <string.h>

/* Wide character string: Remove by discriminating function (isw-style). */
int wcsrmbydfn(wchar_t * ws, int(*discrim)(wint_t));

/* Last character satisfies discriminating function? */
int wcseosdfn(const wchar_t * ws, int(*discrim)(wint_t));

/* Characters satisfy discriminating function? -1: None of them, 0 some, 1 all*/
int wcssatdfn(const wchar_t * ws, int(*discrim)(wint_t));

/* Checks if a wcs has a certain prefix */
int wcspfx(const wchar_t * ws, const wchar_t * px);

/* Checks if a wcs has a certain suffix */
int wcssfx(const wchar_t * ws, const wchar_t * sx);

/* Checks if a string (not wide!) has a certain suffix */
int strpfx(const char * s, const char * px);

#endif