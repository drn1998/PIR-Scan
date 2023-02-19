#include <wchar.h>
#include <stdbool.h>

#include "stem.h"

int wcssfx(const wchar_t * ws, const wchar_t * sx)
{
    if (!ws || !sx)
        return 0;
    size_t lenstr = wcslen(ws);
    size_t lensuffix = wcslen(sx);
    if (lensuffix >  lenstr)
        return 0;
    return wcsncmp(ws + lenstr - lensuffix, sx, lensuffix) == 0;
}

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
