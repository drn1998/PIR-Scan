#include <locale.h>

#include "../eval.h"

int main() {
    setlocale(LC_ALL, "");
    wchar_t * tokens[] = {L"neue", L"Musik"};
    char pir[3] = {'2', '3', '5'};
    load_stopwords("stopwords_11032023");
    int res_001 = eval(tokens, 2, pir, true, NULL, 0);

    if(res_001 == 1) {
        wprintf(L"OK: Correctly evaluated double tokens with stopwords loaded as matching.\n");
    } else {
        wprintf(L"ERR: Incorrectly evaluated double tokens as non-matching.\n");
    }
    free_stopwords();
    return 0;
}