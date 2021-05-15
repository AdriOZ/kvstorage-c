#include "btree.h"
#include "token.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    BinaryTreeNode* tree = NULL;
    Token* tok = NULL;
    const char* error = NULL;
    char input[1024];
    char clear;
    int run = 1;
    int ignore;

    while (run) {
        // Reading
        printf("$> ");
        ignore = scanf("%1023[^\n]", input);
        ignore = scanf("%c", &clear);

        // Parsing
        tok = Tokenize(input);
        error = ValidateToken(tok);

        // Errors
        if (error != NULL) {
            printf("\nError: %s\n\n", error);
            Delete(tok);
            continue;
        }

        // Interpret
        switch (tok->type) {
        case Set:
            if (tree == NULL) {
                tree = CreateBinaryTree(tok->key, tok->value);
            } else {
                PutBinaryTreeNode(tree, tok->key, tok->value);
            }
            break;
        case Get:
            if (tree == NULL) {
                printf("\nError: no data saved yet\n\n");
            } else {
                printf("\n%s\n\n", GetBinaryTreeValue(tree, tok->key));
            }
            break;
        case Store:
            if (tree == NULL) {
                printf("\nError: no data saved yet\n\n");
            } else {
                if (StoreBinaryTree(tok->filename, tree)) {
                    printf("\nData saved into file '%s'\n\n", tok->filename);
                } else {
                    printf("\nError: cannot save data saved into file '%s'\n\n", tok->filename);
                }
            }
            break;
        case Load:
            if (tree != NULL) {
                printf("\nError: cannot override existing data\n\n");
            } else {
                tree = LoadBinaryTree(tok->filename);

                if (tree != NULL) {
                    printf("\nData imported from '%s'\n\n", tok->filename);
                } else {
                    printf("\nError: cannot import data from '%s'\n\n", tok->filename);
                }
            }
            break;
        case Quit:
            run = 0;
            break;
        default:
            break;
        }
        Delete(tok);
    }

    return 0;
}
