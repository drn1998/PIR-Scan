#ifndef STOPWORD_H
#define STOPWORD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

/** @brief The maximum size of a stopword */
#define STOPWORD_BUFFER_SIZE 32

/**
 * @brief A datatype for a single stopword
 * 
 */
typedef struct {
    wchar_t * text; // The stopword
    bool is_cs; // If true, the spelling with first character uppercase is not implied to be a stopword as well
} stopword_t;

extern stopword_t * stopword_v;
extern size_t stopword_n;

int load_stopwords(char * fpth);
int is_stopword(wchar_t * ws);
void free_stopwords();

#endif
