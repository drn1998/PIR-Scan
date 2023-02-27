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

    int res_002 = is_stopword(NULL);
    if(res_002 != -1) {
        wprintf(L"ERR: Statement about stopword provided despite file unloaded.\n");
    } else {
        wprintf(L"OK: Acknowledged unavailable stopword data.\n");
    }

    free_stopwords();

    return 0;
}