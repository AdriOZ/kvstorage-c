#include <stdlib.h>
#include <stdio.h>
#include "btree.h"

int main()
{
    KeyValuePair pairs[] = {
        {"Truck", "White"},
        {"Car", "Red"},
        {"Bike", "Yellow"},
        {"Bus", "Blue"},
        {"Tree", "Green"},
        {"House", "Big"},
    };
    BinaryTreeNode *pre = CreateBinaryTreeFrom(6, pairs);
    StoreBinaryTree("test.btree", pre);
    BinaryTreeNode *post = LoadBinaryTree("test.btree");
    char **postKeys = GetBinaryTreeKeys(post);
    char **postValues = GetBinaryTreeValues(post);

    for (int i = 0; i < 6; ++i)
    {
        printf("%s - %s\n", postKeys[i], postValues[i]);
    }

    return 0;
}
