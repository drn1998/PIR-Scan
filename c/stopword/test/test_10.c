#include <locale.h>

#include "../stopword.h"

int main() {
    setlocale(LC_ALL, "");
    int res_001 = load_stopwords("random");
    if(res_001 != 0) {
        wprintf(L"ERR: Allegedly found stopwords in random data.\n");
    } else {
        wprintf(L"OK: No stopwords found in random data.\n");
    }

    free_stopwords();

    return 0;
}