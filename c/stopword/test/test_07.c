#include <locale.h>

#include "../stopword.h"

int main() {
    setlocale(LC_ALL, "");
    int res_001 = load_stopwords("stopwords_27022023");
    if(res_001 == 788) {
        wprintf(L"OK: All stopwords were loaded and counted.\n");
    } else {
        wprintf(L"ERR: The stopwords have been counted incorrectly.\n");
    }

    int res_002 = is_stopword(L"derzeitiger");
    if(res_002 == 1) {
        wprintf(L"OK: Existing stopword correctly detected.\n");
    } else {
        wprintf(L"ERR: Stopword not detected despite located in file.\n");
    }

    int res_003 = is_stopword(L"obwohl");
    if(res_003 == 1) {
        wprintf(L"OK: Existing stopword correctly detected.\n");
    } else {
        wprintf(L"ERR: Stopword not detected despite located in file.\n");
    }

    int res_004 = is_stopword(L"Historizialität");
    if(res_004 == 0) {
        wprintf(L"OK: Non-stopword was correctly identified as not being a stopword.\n");
    } else {
        wprintf(L"ERR: Non-stopword got detected as an apparent stopword.\n");
    }

    free_stopwords();

    return 0;
}