#include "eval.h"

int eval(const wchar_t * token_wcs, const char pir_match[5], bool exclude_stopword, void(*stem)(wchar_t *), size_t prefix) {
    wchar_t local[TOKEN_SIZE];
    char pir[5];

    if(wcslen(token_wcs) > TOKEN_SIZE - 1) {
        abort();
    }

    wcscpy(local, token_wcs);

    wcsrmbydfn(local, iswpunct);

    if(wcslen(local) == 0) {
        return 0;
    }

    if(exclude_stopword == true) {
        if(is_stopword(local)) {
            return 0;
        }
    }

    if(prefix > 2 && wcslen(local) >= prefix) {
        local[prefix] = '\0';
    } else if (wcslen(local) < prefix) {
        return 0;
    }

    if(stem != NULL && prefix == 0)
        stem(local);

    write_pir_code(local, pir);

    if(strpfx(pir, pir_match)) {
        return 1;
    }

    return 0;
}