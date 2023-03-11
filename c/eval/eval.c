#include "eval.h"

int eval(wchar_t ** token_v, size_t token_n, const char pir_match[PIR_CODE_LENGTH], bool exclude_stopword, void(*stem)(wchar_t *), size_t prefix) {
    wchar_t local[TOKEN_SIZE];
    pir_t pir_code;
    bool stopwords = true;

    for(register size_t i = 0; i < token_n; i++) {
        if(wcslen(token_v[i]) == 0)
            return 0;
    }

    for(register size_t i = 0; i < token_n - 1; i++) {
        if(wcslen(token_v[i]) > 0)
            if(iswpunct(token_v[i][wcslen(token_v[i]) - 1]))    // Better part-of-sentence detection
                return 0;
    }

    if(exclude_stopword == true) {
        for(register size_t i = 0; i < token_n; i++) {
            if(is_stopword(token_v[i]) == 0)
                stopwords = false;
        }

        if(stopwords == true) { return 0; }
    }

    pir_code_init(&pir_code);

    for(register size_t i = 0; i < token_n; i++) {
        wcscpy(local, token_v[i]);
        wcsrmbydfn(local, iswpunct);
        if(stem != NULL) {
            stem(local);
        }
        if(prefix != 0 && wcslen(local) >= prefix) {
            local[prefix] = '\0';
        } else if (wcslen(local) < prefix) {
            return 0;
        }
        pir_code_write(local, &pir_code);
        if(i != token_n - 1) {
            pir_code_write(L" ", &pir_code);
        }
    }

    if(!strpfx(pir_code.pir, pir_match))
        return 0;

    return 1;
}