#include <stdio.h>
#include "stopword.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    if(load_stopwords("german.csv") == -1) {
        wprintf(L"Unable to load file.\n");
        return -1;
    }

    if(is_stopword(L"derzeitiger")) {
        wprintf(L"Stopword detected.\n");
    } else {
        wprintf(L"Not a stopword.\n");
    }
    free_stopwords();

    return 0;
}
