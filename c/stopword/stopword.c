#include "stopword.h"

stopword_t * stopword_v;
size_t stopword_n;

int stopword_cmp(const void * a, const void * b) {
    stopword_t _a = *(stopword_t*)a;
    stopword_t _b = *(stopword_t*)b;
    return wcscmp(_a.text, _b.text);
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
    stopword_t * new_memory;
    size_t cs_buffer;
    size_t stopword_a;

    fp = fopen(fpth, "r");

	if(fp == NULL) { return -1; }

    new_memory = NULL;

    stopword_a = 32;
    stopword_n = 0;

	stopword_v = calloc(stopword_a, sizeof(stopword_t));

    cs_buffer = 0;

    while(fwscanf(fp, L"%ls %u", buffer, &cs_buffer) == 2) {
        stopword_v[stopword_n].text = calloc(wcslen(buffer) + 1, sizeof(wchar_t));
        if(stopword_v[stopword_n].text == NULL) {
            fclose(fp);
            free_stopwords();
            return -1;
        }
        wcscpy(stopword_v[stopword_n].text, buffer);
        if(cs_buffer == 1)
            stopword_v[stopword_n].is_cs = true;
        else
            stopword_v[stopword_n].is_cs = false;
        stopword_n++;
        if(stopword_a == stopword_n) {
            stopword_a *= 2;
            new_memory = realloc(stopword_v, stopword_a * sizeof(stopword_t));
            if(new_memory == NULL) {
                fclose(fp);
                free_stopwords();
                return -1;
            } else {
                stopword_v = new_memory;
            }
        }
    }

    fclose(fp);

    stopword_a = stopword_n;
    new_memory = realloc(stopword_v, stopword_a * sizeof(stopword_t));

    if(new_memory == NULL) {
        free_stopwords();
        return -1;
    }

    stopword_v = new_memory;

    qsort(stopword_v, stopword_n, sizeof(stopword_t), stopword_cmp);
    if(!unique(stopword_v, stopword_n, sizeof(stopword_t), stopword_cmp)) { return -1; }

    return stopword_n + 1;
}

int is_stopword(wchar_t * ws) {
    stopword_t key;
    stopword_t * result;

    key.text = calloc(wcslen(ws) + 1, sizeof(wchar_t));

    if(key.text == NULL)
        abort();

    wcscpy(key.text, ws);

    key.text[0] = towlower(ws[0]);

    key.is_cs = false;

    result = bsearch(&key, stopword_v, stopword_n, sizeof(stopword_t), stopword_cmp);

    free(key.text);

    if(result == NULL)
        return 0;

    if(result->is_cs == false)
        return 1;
    
    if(iswupper(ws[0]) && result->is_cs == true)
        return 0;
    else
        return 1;
}

void free_stopwords() {
    register unsigned int j;

    for (j = 0; j < stopword_n; j++) {
		free(stopword_v[j].text);
	}

	free(stopword_v);

    return;
}