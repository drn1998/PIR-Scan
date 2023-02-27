#include <locale.h>

#include "../stopword.h"

int main() {
    setlocale(LC_ALL, "");

    // Redundant call to free_stopwords()

    free_stopwords();

    return 0;
}