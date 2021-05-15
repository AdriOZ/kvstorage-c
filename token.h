#pragma once

// The types of tokens that will be parsed
typedef enum
{
    Set,
    Get,
    Store,
    Load,
    Quit
} TokenType;

// A token parsed from the input
typedef struct
{
    TokenType type;
    char *key;
    char *value;
    char *filename;
} Token;
