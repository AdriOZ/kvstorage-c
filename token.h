#pragma once

// The types of tokens that will be parsed
typedef enum {
    Set,
    Get,
    Store,
    Load,
    Quit,
    Unknown
} TokenType;

// A token parsed from the input
typedef struct
{
    TokenType type;
    char* key;
    char* value;
    char* filename;
} Token;

// Returns the token of an specific expression.
// As only single expressions will be interpreted,
// there is no need to implement
// tokenizer - parser - AST - interpreter
Token* Tokenize(const char* expression);

// Checks if a token is valid. Returns the error
// string or null if everything is fine.
const char* ValidateToken(Token* tok);

// Frees the memory of the token.
void DeleteToken(Token* tok);
