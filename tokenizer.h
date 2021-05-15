#pragma once

typedef struct
{
    const char* source;
    const char* begin;
    const char* end;
    char* index;
} Tokenizer;

Tokenizer* CreateTokenizer(const char* source);
