#include <wchar.h>
#include <wctype.h>
#include <stdio.h>

#include "eval.h"
#include "../stem/stem.h"

int main(int argc, char * argv[]) {
    char pir[PIR_CODE_LENGTH] = {'3', '\0', '\0', '\0', '\0'};
    int result;

    setlocale(LC_ALL, "");

    load_stopwords("german.csv");

    result = eval(L"derzeitige", pir, true, wcsrmsfx);

    wprintf(L"\n%d", result);

    free_stopwords();
}