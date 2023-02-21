#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

#include "string-util.h"

int main(int argc, char* argv[]) {
    wchar_t test_1[] = L"Der 3. Versuch";
    wchar_t test_2[] = L"4895";
    wchar_t test_3[] = L"3";
    wchar_t test_4[] = L"Test";

    setlocale(LC_ALL, "");

    wprintf(L"%i ", wcssatdfn(test_1, iswdigit));
    wprintf(L"%i ", wcssatdfn(test_2, iswdigit));
    wprintf(L"%i ", wcssatdfn(test_3, iswdigit));
    wprintf(L"%i ", wcssatdfn(test_4, iswdigit));

    return 0;
}