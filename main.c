#include "btree.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    KeyValuePair pairs[] = {
        { "Truck", "White" },
        { "Car", "Red" },
        { "Bike", "Yellow" },
        { "Bus", "Blue" },
        { "Tree", "Green" },
        { "House", "Big" },
    };
    BinaryTreeNode* pre = CreateBinaryTreeFrom(6, pairs);
    StoreBinaryTree("test.btree", pre);
    BinaryTreeNode* post = LoadBinaryTree("test.btree");
    char** postKeys = GetBinaryTreeKeys(post);
    char** postValues = GetBinaryTreeValues(post);

    for (int i = 0; i < 6; ++i) {
        printf("%s - %s\n", postKeys[i], postValues[i]);
    }
    printf("%s\n", ValidateToken(NULL));
    printf("%s\n", ValidateToken(Tokenize("asf  asdfaasd ")));
    printf("%s\n", ValidateToken(Tokenize("GET")));
    printf("%s\n", ValidateToken(Tokenize("SET")));
    printf("%s\n", ValidateToken(Tokenize("STORE")));
    printf("%s\n", ValidateToken(Tokenize("LOAD")));
    return 0;
}
