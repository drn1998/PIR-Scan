#include <locale.h>

#include "../eval.h"

int main() {
    setlocale(LC_ALL, "");
    wchar_t * tokens[] = {L"allerdings", L"nur"};
    char pir[3] = {'\0', '\0', '\0'};
    load_stopwords("stopwords_11032023");
    int res_001 = eval(tokens, 2, pir, true, NULL, 0);

    if(res_001 == 0) {
        wprintf(L"OK: Sequence of only stopwords evaluated as non-matching.\n");
    } else {
        wprintf(L"ERR: Incorrectly evaluated tokens of only stopwords as matching.\n");
    }
    free_stopwords();
    return 0;
}