#include "eval.h"

int eval(wchar_t ** token_v, size_t token_n, const char pir_match[PIR_CODE_LENGTH], bool exclude_stopword, void(*stem)(wchar_t *), size_t prefix) {
    wchar_t local[TOKEN_SIZE];
    char pir[PIR_CODE_LENGTH];
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

    for(register size_t i = 0; i < token_n; i++) {
        wcscpy(local, token_v[i]);
        wcsrmbydfn(local, iswpunct);
        wprintf(L"%ls ", local);
    }

    wprintf(L"\n");

    return 1;
}