#include "stopword.h"

wchar_t ** stopwords;
unsigned int stopword_iterator;

int wcscmp_sort(const void * a, const void * b) {
    const wchar_t * aa = *(const wchar_t **)a;
    const wchar_t * bb = *(const wchar_t **)b;
    return wcscmp(aa, bb);
}

int unique(const void * base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
    unsigned register int i;

    for (i = 1; i < nmemb; i++) {
        if(compar(base + (i - 1) * size, base + i * size) == 0) {
            return 0;
        }
    }

    return 1;
}

int load_stopwords(char * fpth) {
    FILE * fp;
    wchar_t buffer[STOPWORD_BUFFER_SIZE];

    fp = fopen(fpth, "r");

	if(fp == NULL) { return -1; }

	stopwords = calloc(stopword_iterator + 1, sizeof(wchar_t *));

	while(fgetws(buffer, STOPWORD_BUFFER_SIZE, fp) != NULL) {
		stopwords[stopword_iterator] = calloc(wcslen(buffer) + 1, sizeof(wchar_t));
		wcsncpy(stopwords[stopword_iterator], buffer, wcslen(buffer) - 1); stopword_iterator++;
		stopwords = realloc(stopwords, (stopword_iterator + 1) * sizeof(wchar_t *));
	}

	fclose(fp);

    qsort(stopwords, stopword_iterator, sizeof(wchar_t*), wcscmp_sort);

    if(!unique(stopwords, stopword_iterator, sizeof(wchar_t*), wcscmp_sort)) { return -1; }

    return 0;
}

int is_stopword(wchar_t * ws) {
    if(bsearch(&ws, stopwords, stopword_iterator, sizeof(wchar_t*), wcscmp_sort) == NULL) {
        return 0;
    } else {
        return 1;
    }
}

void free_stopwords() {
    register unsigned int j;

    for (j = 0; j < stopword_iterator; j++) {
		free(stopwords[j]);
	}

	free(stopwords);

    return;
}
