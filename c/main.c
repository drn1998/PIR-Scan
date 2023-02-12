#include <wchar.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

/* TODO
*  Allocate (and free) Tokens in loop to not affect inter-files
*  "flush" the last tokens so they also get evaluated
*/

typedef struct token {
    wchar_t * value;
    wchar_t follows;
} token_t;

typedef struct result {
    wchar_t * key;
    wchar_t * context;
    wchar_t * section;  // usually the filename
    unsigned int rank;
} result_t;

size_t token_count;
size_t token_alloc;
size_t token_size;
size_t token_n;

wchar_t * token_buffer;

char pir_match[5] = {'3', '8', '\0', '\0', '\0'};

bool stem = true;

int cmpres(const void *a, const void *b) {

    result_t * res_a = (result_t *)a;
    result_t * res_b = (result_t *)b;

    return (wcscmp(res_a->key, res_b->key));
}

int eval(wchar_t * token) {
    // TODO remove non_alphabetic characters
    // TODO is stopword (*)
    // TODO resolve abbreviation

    wchar_t * local;
    char pir[5];

    local = calloc(wcslen(token) + 1, sizeof(wchar_t));
    wcscpy(local, token);

    if(stem)
        wcsrmsfx(local);

    write_pir_code(local, pir);

    free(local);

    if(strpfx(pir_match, pir))
        return 1;

    return 0;
}

int main(int argc, char* argv[]) {
    token_count = 3;
    token_alloc = token_count * 2 + 1;
    token_size = 64;
    token_n = 0;

    token_buffer = NULL;
    wchar_t * context_buffer = NULL;

    char ** files = NULL;
    size_t file_count = 1;

    token_t * tokens = NULL;
    result_t * results = NULL;
    size_t result_alloc = 1;

    char path[] = "textfiles/";
    char * file_path = NULL;

    DIR * dp;
    struct dirent * ep;

    FILE * rf;

    setlocale(LC_ALL, "");

    dp = opendir(path);

    if (dp != NULL)
    {
        files = calloc(file_count, sizeof(char*));

        while ((ep = readdir (dp)) != NULL)
        if(ep->d_type == DT_REG) {
            files[file_count - 1] = malloc(strlen(ep->d_name) + 1);
            strcpy(files[file_count - 1], ep->d_name);
            file_count++;
            files = realloc(files, file_count * sizeof(char*));
        }
        closedir (dp);
      }
      else
      {
        wprintf(L"Unable to open directory '%s'", path);
        return -1;
      }

    if(file_count == 1) {
        wprintf(L"The directory '%s' is empty. It does not contain ordinary files.\n", path);
        goto clear;
    }

    size_t context_buffer_size = (token_alloc * token_size) + 12;
    context_buffer = calloc(context_buffer_size, sizeof(wchar_t));

    results = calloc(result_alloc, sizeof(result_t));

    // Main loop, iterates through files
    for(register unsigned int i = 0; i < file_count - 1; i++) {
        file_path = calloc(sizeof(char), strlen(path) + strlen(files[i]) + 1);

        strcat(file_path, path);
        strcat(file_path, files[i]);

        rf = fopen(file_path, "r");

        token_n = 0;

        if(rf == NULL) {
            wprintf(L"Unable to read from file %s (ignored)", file_path);
            free(file_path);
            continue;
        }

        token_buffer = calloc(sizeof(wchar_t), token_size);

        if(token_buffer == NULL) abort();

        tokens = calloc(token_alloc, sizeof(token_t));

        if(tokens == NULL) {
            wprintf(L"Unable to allocate %u byte(s) of memory.\n", token_alloc * sizeof(token_t));
            goto clear;
        }

        for(register unsigned int i = 0; i < token_alloc; i++) {
            tokens[i].value = calloc(sizeof(wchar_t), token_size);
            if(tokens[i].value == NULL)
                abort();
        }

        wint_t is_eof = 1;
        size_t decrement_token_count = token_count;

        // "Flush" the last tokens by running fwscanf not in head but have to loop run token_count times after EOF
        while(decrement_token_count > 1) { // TODO constand width, to be adapted

            if(is_eof == EOF) {
                decrement_token_count--;
                wmemset(token_buffer, L'\0', token_size);
            } else {
                is_eof = fwscanf(rf, L"%64ls", token_buffer);
            }

            wcscpy(tokens[token_n % token_alloc].value, token_buffer);

            token_n++;

            // Eval
            if(eval(tokens[(token_n + token_count) % token_alloc].value)) {
                wmemset(context_buffer, L'\0', context_buffer_size);
                swprintf(context_buffer, context_buffer_size, L"[...] ");
                for(register unsigned j = 0; j < token_alloc - (is_eof != EOF ? 0 : token_count); j++) {
                    if(wcslen(tokens[(token_n + j) % token_alloc].value) > 0)
                        swprintf(context_buffer + wcslen(context_buffer), context_buffer_size - wcslen(context_buffer), L"%ls ", tokens[(token_n + j) % token_alloc].value);
                }
                swprintf(context_buffer + wcslen(context_buffer), context_buffer_size - wcslen(context_buffer), L"[...]\n\n");

                results[result_alloc - 1].context = calloc(wcslen(context_buffer) + 1, sizeof(wchar_t));
                wcscpy(results[result_alloc - 1].context, context_buffer);

                results[result_alloc - 1].key = calloc(wcslen(tokens[(token_n + token_count) % token_alloc].value) + 1, sizeof(wchar_t));
                wcscpy(results[result_alloc - 1].key, tokens[(token_n + token_count) % token_alloc].value);

                results[result_alloc - 1].section = calloc(strlen(files[i]) + 1, sizeof(wchar_t)); // SIC
                swprintf(results[result_alloc - 1].section, strlen(files[i]) + 1, L"%s", files[i]);

                results[result_alloc - 1].rank = token_n;

                result_alloc++;
                results = realloc(results, sizeof(result_t) * result_alloc);
            }
        }

        for(register unsigned int i = 0; i < token_alloc; i++) {
            free(tokens[i].value);
        }

        if(tokens != NULL)
            free(tokens);

        fclose(rf);

        free(token_buffer);

        free(file_path);
    }

    //qsort(results, result_alloc, sizeof(result_t), cmpres);

    for(register unsigned int i = 0; i < result_alloc - 1; i++) {
        wprintf(L"Found '%ls' in %ls:\n%ls", results[i].key, results[i].section, results[i].context);
    }

    // Stats
    wprintf(L"Matches:\t%u\nFiles:\t%u", result_alloc - 1, file_count - 1);

    clear:
    for(register unsigned int i = 0; i < file_count - 1; i++) {
        free(files[i]);
    }

    if(files != NULL)
        free(files);

    for(register unsigned int i = 0; i < result_alloc - 1; i++) {
        free(results[i].context);
        free(results[i].key);
        free(results[i].section);
    }

    free(results);
    free(context_buffer);
}
