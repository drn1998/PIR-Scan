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

extern stopword_t * stopword_v; // The vector of stopwords
extern size_t stopword_n; // The number of stopwords

/**
 * @brief Load stopwords from file
 * 
 * @param fpth Path to the stopword file
 * @return The number of stopwords loaded, or -1 on an error
 */
int load_stopwords(char * fpth);
/**
 * @brief Tests if a given word is a stopword (required successful loading in advance)
 * 
 * @param ws The string to be tested
 * @return 1, if the word is a stopword, otherwise 0
 */
int is_stopword(wchar_t * ws);
/**
 * @brief Frees the memory allocated for the stopwords caused by a successful call to load_stopwords() when stopword checking functionality is no longer needed for the remaining runtime.
 * 
 */
void free_stopwords();

#endif
