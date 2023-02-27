#include <locale.h>

#include "../stopword.h"

int main() {
    setlocale(LC_ALL, "");

    int res_001 = is_stopword(NULL);
    if(res_001 != -1) {
        wprintf(L"ERR: Statement about stopword provided despite stopwords not loaded.\n");
    } else {
        wprintf(L"OK: Acknowledged unavailable stopword data.\n");
    }

    return 0;
}