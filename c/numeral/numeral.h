#ifndef NUMERAL_H
#define NUMERAL_H

#include <wchar.h>

// This is meant to be expanded to include all kinds of numerals, also ３, 𐅕, ⅷ, ६, ⚄, ...

wint_t numeral_v[] = {L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9'};

int iswnumeral(wint_t __wc);

#endif