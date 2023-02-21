#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Removes characters from a string by a wctype-style discriminating function.
 * 
 * @param ws The wide string where the characters are to be removed from (in place)
 * @param discrim The discriminating function
 * @return Number of characters removed
 */
int wcsrmbydfn(wchar_t * ws, int(*discrim)(wint_t));

/**
 * @brief Checks if the last character of a string satisfies a discriminating function.
 * 
 * @param ws The wide string from which the last character is to be tested
 * @param discrim The discriminating function
 * @return 1, if the last character satisfies the function, otherwise 0
 */
int wcseosdfn(const wchar_t * ws, int(*discrim)(wint_t));

/**
 * @brief Checks if the characters of the function (all, some, none) satisfy a discriminating function.
 * 
 * @param ws The wide string from which the characters are to be tested
 * @param discrim The discriminating function
 * @return 1 if all characters satisfy the function, 0 if at least one character satisfies the function, and -1 if no characters satisfy the function or the length of the string is 0.
 */
int wcssatdfn(const wchar_t * ws, int(*discrim)(wint_t));

/* Checks if a wcs has a certain prefix */
int wcspfx(const wchar_t * ws, const wchar_t * px);

/* Checks if a wcs has a certain suffix */
int wcssfx(const wchar_t * ws, const wchar_t * sx);

/* Checks if a string (not wide!) has a certain suffix */
int strpfx(const char * s, const char * px);

#endif