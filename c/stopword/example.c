#include <stdio.h>
#include "stopword.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    wchar_t buffer[STOPWORD_BUFFER_SIZE];

    if(argc != 2) {
        wprintf(L"Usage: %s [word]\n", argv[0]);
        return 0;
    }

    swprintf(buffer, STOPWORD_BUFFER_SIZE, L"%s", argv[1]);

    if(load_stopwords("german.csv") == -1) {
        wprintf(L"Unable to load file.\n");
    } else {
        if(is_stopword(buffer)) {
            wprintf(L"'%ls' is a stopword\n", buffer);
        } else {
            wprintf(L"'%ls' is not a stopword\n", buffer);
        }

        free_stopwords();
    }

    return 0;
}
