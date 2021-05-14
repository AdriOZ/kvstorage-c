#include <stdlib.h>
#include <stdio.h>
#include "btree.h"

int main()
{
    KeyValuePair pairs[4] = {
        {"Car", "Red"},
        {"Bike", "Yellow"},
        {"Truck", "White"},
        {"Bus", "Blue"},
    };
    BinaryTreeNode *head = CreateBinaryTreeFrom(4, pairs);

    char **keys = GetBinaryTreeKeys(head);
    char **values = GetBinaryTreeValues(head);

    for (int i = 0; i < 4; ++i)
    {
        printf("Vehicle %s is %s\n", keys[i], values[i]);
    }

    return 0;
}
