#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include <getopt.h>

#include "dir-iterator/dir-iterator.h"
#include "eval/eval.h"
#include "stem/stem.h"
#include "string-util/string-util.h"
#include "stopword/stopword.h"

#define DEFAULT_FONT_SIZE 6
#define MAXIMUM_FONT_SIZE 30

#define DEFAULT_COL_COUNT 4
#define MAXIMUM_COL_COUNT 12

/**
 * @brief Datatype for a token, having a value and (currently unused) a character immediatly following that token in the source text.
 * 
 */
typedef struct token {
    wchar_t value[TOKEN_SIZE]; // The "value", e.g. literal string of the token
    wchar_t follows; // The character immediatly following the token to tell end of ordinary sentences apart from end of paragraphs in the future.
} token_t;

/**
 * @brief Datatype for a result; an instance of a token that satisfied the provided search conditions
 * 
 */
typedef struct result {
    wchar_t * key;  // The token that was matched
    wchar_t * context;  // A part from the text where the token was found
    wchar_t * section;  // The section where it was found (usually the filename)
    unsigned int rank;
} result_t;

token_t * token_v = NULL;  // Vector of token_n tokens
size_t token_n;     // Numer of tokens in the cyclic array
size_t token_c;     // Tokens alltogether, not just size of cyclic array

result_t * result_v;    // Vector of result_t results
size_t result_n = 0;    // Number of existing results
size_t result_a = 16;    // Number of allocated results

wchar_t * context_buffer = NULL;   // Buffer for the context string in the result
size_t context_buffer_size; // Size of the buffer where the context string written to result_t is copied

bool include_stopwords = false;
bool directory_opened = false;

/**
 * @brief Compares two wide character strings without regarding upper/lower case.
 * 
 * @param a The first string to be compared
 * @param b The second string to be compared
 * @return 0, if equal, otherwise -1 or 1 depending on lexical priority
 */
int wcscicmp(const wchar_t *a, const wchar_t *b)
{
    for (;; a++, b++) {
        int d = towlower((wint_t)*a) - towlower((wint_t)*b);
        if (d != 0 || !*a)
            return d;
    }
}

/**
 * @brief A qsort-style comparison method for the datatype result_t, comparing by the key.
 * 
 * @param a The first result_t object to be compared
 * @param b The second result_t object to be compared
 * @return 0, if equal, otherwise -1 or 1 depending on lexical priority
 */
int cmpres(const void *a, const void *b) {
    // TODO Case-insensitive sort
    result_t res_a = *(result_t *)a;
    result_t res_b = *(result_t *)b;

    return (wcscicmp(res_a.key, res_b.key));
}

void print_usage() {
    wprintf(L"Usage: pir-scan --path path-to-dir --pir pir-code --output file\n");
    return;
}

void cleanup() {
    if(directory_opened == true)
        close_directory();
    
    if(include_stopwords == false)
        free_stopwords();
    
    if(context_buffer != NULL) {
        free(context_buffer);
        context_buffer = NULL;
    }

    for(register size_t i = 0; i < result_n; i++) {
        free(result_v[i].key);
        free(result_v[i].context);
        free(result_v[i].section);
    }

    free(result_v);

    return;
}

int main(int argc, char* argv[]) {
    char * directory_path = NULL;   // The path of the directory with the relevant text files
    char * pir_code = NULL; // The PIR code that is matched against by pir-scan
    char * output = NULL;  // The filename of the output file where results are written to
    char * current_file = NULL; // The file currently scanned

    wchar_t token_buffer[TOKEN_SIZE];   // Buffer for current token read by fscanf

    FILE * fp_read; // File pointer to the current input file being read
    FILE * fp_write; // File pointer to the output file written to

    wint_t is_eof;
    size_t decrement_token_count;

    void (*stemmer)(wchar_t*) = NULL;

    size_t context_length = 3;  // Number of tokens displayed before and after matching token

    size_t prefix = 0;

    size_t html_fontsize = DEFAULT_FONT_SIZE;
    size_t html_columns = DEFAULT_COL_COUNT;

    result_t * realloc_address;

    int opt = 0;
    int long_index = 0;

    static struct option long_options[] = {
        {"path", required_argument, 0, 'p'},
        {"pir", required_argument, 0, 'c'},
        {"include-stopwords", no_argument, 0, 'x'},
        {"use-stemming", no_argument, 0, 's'},
        {"context-length", required_argument, 0, 'n'},
        {"output", required_argument, 0, 'o'},
        {"prefix", required_argument, 0, 'P'},
        {"html-fontsize", required_argument, 0, 'f'},
        {"html-columns", required_argument, 0, 'C'},
        {0, 0, 0, 0}
    };

    setlocale(LC_ALL, "");

    while ((opt = getopt_long(argc, argv,"C:f:P:p:c:n:o:xs", 
                   long_options, &long_index )) != -1) {
        switch (opt) {
             case 'p' : directory_path = optarg;
                 break;
             case 'c' : pir_code = optarg;
                 break;
             case 'n' : context_length = atoi(optarg);
                 break;
             case 'x' : include_stopwords = true;
                 break;
             case 's' : stemmer = wcsrmsfx;
                 break;
             case 'o' : output = optarg;
                 break;
             case 'P' : prefix = atoi(optarg);
                 break;
             case 'f' : html_fontsize = atoi(optarg);
                 break;
             case 'C' : html_columns = atoi(optarg);
                 break;
             default: print_usage(); 
                 exit(EXIT_FAILURE);
        }
    }

    if(directory_path == NULL || pir_code == NULL || output == NULL || context_length == 0) {
        print_usage();
        exit(EXIT_FAILURE);
    }

    if(load_directory_by_path(directory_path) == -1) {
        wprintf(L"Unable to load directory %s\n", directory_path);
        exit(EXIT_FAILURE);
    } else {
        directory_opened = true;
    }

    if(include_stopwords == false) {
        if(load_stopwords("german.csv") == -1) {
            wprintf(L"Unable to load stopwords.\n");
            include_stopwords = true; // In order to not load them in cleanup()
            cleanup();
            exit(EXIT_FAILURE);
        }
    }

    if((prefix < 3 || prefix > 8) && prefix != 0) {
        wprintf(L"Invalid prefix length: Must be in range 3 to 8.\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    if(prefix != 0 && stemmer != NULL) {
        wprintf(L"Error: Prefix and stemming cannot coexist.\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    if(html_fontsize > MAXIMUM_FONT_SIZE) {
        html_fontsize = MAXIMUM_FONT_SIZE;
    }

    if(html_fontsize == 0) {
        html_fontsize = 1;
    }

    if(html_columns > MAXIMUM_COL_COUNT) {
        html_columns = MAXIMUM_COL_COUNT;
    }

    if(html_columns == 0) {
        html_columns = 1;
    }
    
    token_n = context_length * 2 + 1;
    current_file = next_filename();

    context_buffer_size = token_n * TOKEN_SIZE + 12;
    context_buffer = calloc(context_buffer_size, sizeof(wchar_t));
    if(context_buffer == NULL) {
        cleanup();
        exit(EXIT_FAILURE);
    }

    result_v = calloc(result_a, sizeof(result_t));
    if(result_v == NULL) {
        cleanup();
        exit(EXIT_FAILURE);
    }

    while(current_file != NULL) {
        fp_read = fopen(current_file, "r");

        if(fp_read == NULL) {
            wprintf(L"Unable to read file '%s'.\n", current_file);
            cleanup();
            exit(EXIT_FAILURE);
        }

        token_v = calloc(token_n, sizeof(token_t));

        if(token_v == NULL) {
            wprintf(L"Unable to allocate memory for cyclic array of tokens.\n");
            fclose(fp_read);
            cleanup();
            exit(EXIT_FAILURE);
        }

        is_eof = 1; // Why start with 1?
        token_c = 0;
        decrement_token_count = context_length;

        while(decrement_token_count > 1) { // > 0 ?
            if(is_eof == EOF) {
                decrement_token_count--;
                wmemset(token_buffer, L'\0', TOKEN_SIZE);
            } else {
                is_eof = fwscanf(fp_read, L"%64ls", token_buffer);
            }

            wcscpy(token_v[token_c % token_n].value, token_buffer);

            token_c++;

            if(eval(token_v[(token_c + context_length) % token_n].value, pir_code, !include_stopwords, stemmer, prefix)) {
                wmemset(context_buffer, L'\0', context_buffer_size);
                swprintf(context_buffer, context_buffer_size, L"[…] ");
                for(register unsigned j = 0; j < context_length + decrement_token_count; j++) {
                    if(j == context_length)
                        swprintf(context_buffer + wcslen(context_buffer), context_buffer_size - wcslen(context_buffer), L"<u>");
                    if(wcslen(token_v[(token_c + j) % token_n].value) > 0)
                        swprintf(context_buffer + wcslen(context_buffer), context_buffer_size - wcslen(context_buffer), L"%ls ", token_v[(token_c + j) % token_n].value);
                    if(j == context_length)
                        swprintf(context_buffer + wcslen(context_buffer) - 1, context_buffer_size - wcslen(context_buffer), L"</u> ");
                }
                swprintf(context_buffer + wcslen(context_buffer) - 1, context_buffer_size - wcslen(context_buffer), L"&nbsp;[…]");

                result_v[result_n].key = calloc(wcslen(token_v[(token_c + context_length) % token_n].value) + 1, sizeof(wchar_t));
                wcscpy(result_v[result_n].key, token_v[(token_c + context_length) % token_n].value);

                wcsrmbydfn(result_v[result_n].key, iswpunct);

                result_v[result_n].context = calloc(wcslen(context_buffer) + 1, sizeof(wchar_t));
                wcscpy(result_v[result_n].context, context_buffer);

                result_v[result_n].section = calloc(strlen(current_file) + 1, sizeof(wchar_t));
                swprintf(result_v[result_n].section, strlen(current_file) + 1, L"%s", current_file);

                result_v[result_n].rank = token_n;

                result_n++;

                if(result_n == result_a) {
                    result_a *= 2;
                    realloc_address = realloc(result_v, result_a * sizeof(result_t));
                    if(realloc_address == NULL) {
                        cleanup();
                        exit(EXIT_FAILURE);
                    }
                    result_v = realloc_address;
                }
            }
        }

        free(token_v);
        fclose(fp_read);

        current_file = next_filename();
    }

    result_a = result_n;

    realloc_address = realloc(result_v, result_a * sizeof(result_t));
    if(realloc_address == NULL) {
        cleanup();
        exit(EXIT_FAILURE);
    }
    result_v = realloc_address;

    qsort(result_v, result_n, sizeof(result_t), cmpres);

    fp_write = fopen(output, "w");

    if(fp_write == NULL) {
        wprintf(L"Unable to open output file '%s'\n", output);
        cleanup();
        exit(EXIT_FAILURE);
    }

    fwprintf(fp_write, L"<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<title>%s</title>\n\t\t<style>\n\t\t\tp {\n\t\t\t\tfont-family: sans-serif;\n\t\t\t\tfont-size: %upt;\n\t\t\t}\n\t\t\tdiv {\n\t\t\t\tcolumn-count: %u;\n\t\t\t}\n\t\t\t</style>\n\t</head>\n\t<body>\n\t\t<h1 style=\"font-family: sans-serif;\">%s</h1>\n\t\t<div>", output, html_fontsize, html_columns, output);

    for(register unsigned int i = 0; i < result_n; i++) {
        if(i > 0) {
            if(wcscmp(result_v[i].key, result_v[i - 1].key) != 0)
                fwprintf(fp_write, L"</p>\n\t\t<p><strong>%ls</strong> found in %ls:<br/>", result_v[i].key, result_v[i].section);
        } else {
            fwprintf(fp_write, L"\n\t\t<p><strong>%ls</strong> found in %ls:<br/>", result_v[i].key, result_v[i].section);
        }
        fwprintf(fp_write, L"\n\t\t%ls<br/>", result_v[i].context);
    }

    fwprintf(fp_write, L"\n\t\t</div>\n\t</body>\n</html>");

    fclose(fp_write);

    cleanup();
    exit(EXIT_SUCCESS);
}