#include <stdlib.h>
#include <stdio.h>
#include "btree.h"

int main()
{
    KeyValuePair pairs[] = {
        {"Monty", "White"},
        {"Nala", "Orange"},
        {"Simba", "Grey"},
        {"Mika", "Brown"},
        {"Garfield", "Orange"},
    };
    BinaryTreeNode *head = CreateBinaryTreeFrom(5, pairs);

    char **keys = GetBinaryTreeKeys(head);
    char **values = GetBinaryTreeValues(head);

    for (int i = 0; i < 5; ++i)
    {
        printf("Cat %s = %s\n", keys[i], values[i]);
    }

    return 0;
}
