#ifndef STEM_H
#define STEM_H

#include "../string-util/string-util.h"

/**
 * @brief Remove characters based on the stemming rule
 * 
 * @param ws The wide string to be stemmed (modified in place)
 */
void wcsrmsfx(wchar_t * ws);

#endif
