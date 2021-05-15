#include "tokenizer.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

Tokenizer* CreateTokenizer(const char* source)
{
    if (source == NULL) {
        return NULL;
    }
    Tokenizer* tok = New(Tokenizer);
    tok->begin = tok->source = source;
    tok->index = (char*)tok->begin;
    tok->end = strstr(source, "\n");

    if (tok->end == NULL) {
        tok->end = source + strlen(source);
    }
    return tok;
}
