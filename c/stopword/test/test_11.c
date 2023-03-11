#include <locale.h>

#include "../stopword.h"

int main() {
    setlocale(LC_ALL, "");
    int res_001 = load_stopwords("single");
    if(res_001 != 1) {
        wprintf(L"ERR: Wrong count of stopwords in file with single entry.\n");
    } else {
        wprintf(L"OK: Only counted one stopword in file with single stopword.\n");
    }

    int res_002 = is_stopword(L"einzelwort");

    if(res_002 == 1) {
        wprintf(L"OK: Correctly found single stopword in file.\n");
    } else {
        wprintf(L"ERR: Only stopword in file could not be found.\n");
    }

    free_stopwords();

    return 0;
}