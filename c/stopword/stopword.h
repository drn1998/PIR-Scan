#ifndef STOPWORD_H
#define STOPWORD_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#define STOPWORD_BUFFER_SIZE 32

extern wchar_t ** stopwords;
extern unsigned int stopword_iterator;

int wcscmp_sort(const void * a, const void * b);
int unique(const void * base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
int load_stopwords(char * fpth);
int is_stopword(wchar_t * ws);
void free_stopwords();

#endif
