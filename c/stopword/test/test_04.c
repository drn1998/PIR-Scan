#include <locale.h>

#include "../stopword.h"

int main() {
    setlocale(LC_ALL, "");

    // Undefined call to is_stopword(wchar_t*)
    int res_001 = is_stopword(L"Test");
    if(res_001 != -1) {
        wprintf(L"ERR: Statement about stopword provided despite stopwords not loaded.\n");
    } else {
        wprintf(L"OK: Acknowledged unavailable stopword data.\n");
    }

    // Redundant call to free_stopwords()

    free_stopwords();

    return 0;
}