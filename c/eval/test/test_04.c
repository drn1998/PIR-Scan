#include <locale.h>

#include "../eval.h"

int main() {
    setlocale(LC_ALL, "");
    wchar_t * tokens[] = {L"Reaktorkatastrophe"};
    char pir[3] = {'\0', '\0', '\0'};
    int res_001 = eval(tokens, 1, pir, false, NULL, 0);

    if(res_001 == 1) {
        wprintf(L"OK: Correctly evaluated single token with generic PIR code as matching.\n");
    } else {
        wprintf(L"ERR: Incorrectly evaluated single token as non-matching.\n");
    }

    return 0;
}