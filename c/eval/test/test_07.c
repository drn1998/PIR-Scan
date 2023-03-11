#include <locale.h>

#include "../eval.h"

int main() {
    setlocale(LC_ALL, "");
    wchar_t * tokens[] = {L"allenfalls"};
    char pir[3] = {'\0', '\0', '\0'};
    load_stopwords("stopwords_11032023");
    int res_001 = eval(tokens, 1, pir, true, NULL, 0);

    if(res_001 == 0) {
        wprintf(L"OK: Correctly evaluated single stopword token with stopwords loaded as non-matching.\n");
    } else {
        wprintf(L"ERR: Incorrectly evaluated single token as non-matching.\n");
    }
    free_stopwords();
    return 0;
}