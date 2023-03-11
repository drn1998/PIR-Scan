#include <locale.h>

#include "../eval.h"

int main() {
    setlocale(LC_ALL, "");
    wchar_t * tokens[] = {L"Reaktorkatastrophe,"};
    char pir[3] = {'9', '8', '9'};
    load_stopwords("stopwords_11032023");
    int res_001 = eval(tokens, 1, pir, true, NULL, 0);

    if(res_001 == 1) {
        wprintf(L"OK: Correctly evaluated single non-stopword token with stopwords loaded as matching.\n");
    } else {
        wprintf(L"ERR: Incorrectly evaluated single token as non-matching.\n");
    }
    free_stopwords();
    return 0;
}