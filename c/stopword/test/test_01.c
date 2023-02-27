#include <locale.h>

#include "../stopword.h"

int main() {
    setlocale(LC_ALL, "");
    int res_001 = load_stopwords("NOT_A_VALID_FILE");
    if(res_001 == -1) {
        wprintf(L"OK: Non-existent file returns -1\n");
    } else {
        wprintf(L"ERR: Non-existent file did not return -1\n");
    }

    // Undefined call to is_stopword(wchar_t*)
    int res_002 = is_stopword(L"Test");
    if(res_002 != -1) {
        wprintf(L"ERR: Statement about stopword provided despite stopwords not loaded.\n");
    } else {
        wprintf(L"OK: Acknowledged unavailable stopword data.\n");
    }

    // Redundant call to free_stopwords()

    free_stopwords();

    return 0;
}