#include "string-util.h"

int wcsrmbydfn(wchar_t * ws, int(*discrim)(wint_t)) {
    register size_t i, n;

    n = 0;

    for(i = 0; i < wcslen(ws) + 1; i++) {
        if(discrim(ws[i]) == 0) {
            ws[n] = ws[i];
            n++;
        }
    }

    return n;
}

int wcseosdfn(const wchar_t * ws, int(*discrim)(wint_t)) {
    if(discrim(ws[wcslen(ws) - 1]))
        return 1;
    
    return 0;
}

int wcssatdfn(const wchar_t * ws, int(*discrim)(wint_t)) {
    register size_t i, n, len;

    n = 0;

    len = wcslen(ws);

    for (i = 0; i < len; i++) {
        if(discrim(ws[i]) != 0)
            n++;
    }

    if(n == len && len > 0)
        return 1;
    
    if(n > 0)
        return 0;
    
    return -1;
}

int wcspfx(const wchar_t * ws, const wchar_t * px)
{
    return wcsncmp(px, ws, wcslen(px)) == 0;
}

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

int strpfx(const char * s, const char * px)
{
    return strncmp(px, s, strlen(px)) == 0;
}