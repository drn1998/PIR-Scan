#ifndef STOPWORD_H
#define STOPWORD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

#define STOPWORD_BUFFER_SIZE 32

typedef struct {
    wchar_t * text;
    bool is_cs;
} stopword_t;

extern stopword_t * stopword_v;
extern size_t stopword_n;

int load_stopwords(char * fpth);
int is_stopword(wchar_t * ws);
void free_stopwords();

#endif
