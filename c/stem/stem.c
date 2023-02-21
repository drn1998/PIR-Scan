#include <wchar.h>
#include <stdbool.h>

#include "stem.h"

void wcsrmsfx(wchar_t * ws) {
    register unsigned int i;
    bool changed = true;

    wchar_t * array[] = {L"nde", L"in", L"e", L"n", L"r", L"s"};    // Exceptions for 'ss', 'nn', 're', ...?

    while(changed) {
        changed = false;
        for(i = 0; i < sizeof(array) / sizeof(wchar_t *); i++) {
            if(wcssfx(ws, array[i])) {
                ws[wcslen(ws) - wcslen(array[i])] = L'\0';
                changed = true;
            }
        }
    }

    return;
}
