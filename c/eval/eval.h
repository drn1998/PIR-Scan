#ifndef EVAL_H
#define EVAL_H

#include <wchar.h>
#include <wctype.h>
#include <stdbool.h>
#include "../string-util/string-util.h"
#include "../stopword/stopword.h"
#include "../pir-code/pir.h"

#define TOKEN_SIZE 64

int eval(const wchar_t * token_wcs, const char pir_match[5], bool exclude_stopword, void(*stem)(wchar_t *));

#endif