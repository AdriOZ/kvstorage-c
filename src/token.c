#include "token.h"
#include "util.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

Token *Tokenize(const char *expression)
{
    Token *result = New(Token);
    result->type = Unknown;
    result->key = NULL;
    result->value = NULL;
    result->filename = NULL;

    if (expression == NULL)
    {
        return result;
    }
    char *end = (char *)(expression + strlen(expression));
    char *cursor = (char *)expression;

    // Leading white space
    for (; cursor < end && isspace(*cursor); ++cursor)
        ;

    // Instruction
    if (!isalpha(*cursor))
    {
        return result;
    }
    char *subcursor = cursor;
    size_t counter = 0;

    for (; subcursor < end && isalpha(*subcursor); ++subcursor, ++counter)
        ;

    if (counter == 0)
    {
        return result;
    }
    char *instruction = NewArray(char, counter + 2);
    memcpy_s(instruction, counter, cursor, counter);
    instruction[counter] = '\0';

    for (size_t i = 0; i <= counter; ++i)
    {
        instruction[i] = (char)toupper(instruction[i]);
    }

    // Type Quit -> No more processing
    if (strcmp("QUIT", instruction) == 0 || strcmp("EXIT", instruction) == 0)
    {
        Delete(instruction);
        result->type = Quit;
        return result;
    }

    // Next part of the expression (key / filename)
    cursor = subcursor;
    char *part1 = NULL;

    for (; cursor < end && isspace(*cursor); ++cursor)
        ;

    if (cursor < end)
    {
        if (*cursor == '"')
        {
            cursor++;
            subcursor = cursor;
            counter = 0;

            for (; subcursor < end && *subcursor != '"'; ++subcursor, ++counter)
                ;

            if (counter > 0)
            {
                part1 = NewArray(char, counter + 1);
                memcpy_s(part1, counter, cursor, counter);
                part1[counter] = '\0';
            }
            ++subcursor; // Skip '"'
        }
        else if (cursor < end)
        {
            subcursor = cursor;
            counter = 0;

            for (; subcursor < end && !isspace(*subcursor); ++subcursor, ++counter)
                ;

            if (counter > 0)
            {
                part1 = NewArray(char, counter + 1);
                memcpy_s(part1, counter, cursor, counter);
                part1[counter] = '\0';
            }
        }
    }

    // Types Get, Store, Load -> No more processing
    if (strcmp("GET", instruction) == 0 || strcmp("FIND", instruction) == 0)
    {
        Delete(instruction);
        result->type = Get;
        result->key = part1;
        return result;
    }

    if (strcmp("STORE", instruction) == 0 || strcmp("SAVE", instruction) == 0)
    {
        Delete(instruction);
        result->type = Store;
        result->filename = part1;
        return result;
    }

    if (strcmp("LOAD", instruction) == 0)
    {
        Delete(instruction);
        result->type = Load;
        result->filename = part1;
        return result;
    }

    // Type Set
    if (strcmp("SET", instruction) == 0 || strcmp("PUT", instruction) == 0)
    {
        Delete(instruction);
        result->type = Set;
        result->key = part1;

        for (cursor = subcursor; cursor < end && isspace(*cursor); ++cursor)
            ;

        subcursor = cursor;
        counter = 0;

        for (; subcursor < end; ++subcursor, ++counter)
            ;

        if (counter > 0)
        {
            result->value = NewArray(char, counter + 1);
            memcpy_s(result->value, counter, cursor, counter);
            result->value[counter] = '\0';
        }
        return result;
    }
    Delete(part1);
    Delete(instruction);
    return result;
}

const char *ValidateToken(Token *tok)
{
    if (tok == NULL)
    {
        return "Null token passed";
    }
    if (tok->type == Unknown)
    {
        return "Unknown token passed";
    }
    if ((tok->type == Set || tok->type == Get) && (tok->key == NULL))
    {
        return "Key is mandatory for Set and Get operations";
    }
    if ((tok->type == Store || tok->type == Load) && (tok->filename == NULL))
    {
        return "Filename is mandatory for Store and Load operations";
    }
    return NULL;
}

void DeleteToken(Token *tok)
{
    if (tok == NULL)
    {
        return;
    }
    Delete(tok->key);
    Delete(tok->value);
    Delete(tok->filename);
    Delete(tok);
}
