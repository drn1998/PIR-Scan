#include <stdio.h>
#include "stopword.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    if(load_stopwords("german.csv") == -1) {
        wprintf(L"Unable to load file.\n");
    }

    if(is_stopword(L"aller")) {
        wprintf(L"'aller' is a stopword\n");
    }

    if(is_stopword(L"Aller")) {
        wprintf(L"'Aller' is a stopword\n");
    }

    if(is_stopword(L"derzeitiger")) {
        wprintf(L"'derzeitiger' is a stopword\n");
    }

    if(is_stopword(L"Derzeitiger")) {
        wprintf(L"'Derzeitiger' is a stopword\n");
    }

    free_stopwords();

    return 0;
}
