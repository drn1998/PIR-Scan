#include "numeral.h"

int iswnumeral(wint_t __wc) {
    size_t numeral_n = sizeof(numeral_v);

    for(register size_t i = 0; i < numeral_n; i++) {
        if(numeral_v[i] == __wc)
            return 1;
    }

    return 0;
}