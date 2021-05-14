#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "btree.h"

static long Hash(const char *key)
{
    if (key == NULL)
    {
        return 0;
    }

    long hash = 0;
    int index = 0;

    while (key[index] != '\0')
    {
        hash += 31 * hash + key[index];
        ++index;
    }
    return hash;
}

static void Insert(BinaryTreeNode *tree, long id, const char *key, const char *value)
{
    // Equal
    if (id == tree->id)
    {
        Delete(tree->value);

        if (value != NULL)
        {

            tree->value = NewArray(char, strlen(value));
            strcpy(tree->value, value);
        }
        return;
    }

    // Greater than
    if (id > tree->id)
    {
        if (tree->right == NULL)
        {
            tree->right = New(BinaryTreeNode);
            tree->right->id = id;
            tree->right->left = NULL;
            tree->right->right = NULL;
            tree->right->key = NewArray(char, strlen(key));
            strcpy(tree->right->key, key);

            if (value != NULL)
            {

                tree->right->value = NewArray(char, strlen(value));
                strcpy(tree->right->value, value);
            }
            else
            {
                tree->right->value = NULL;
            }
        }
        else
        {
            Insert(tree->right, id, key, value);
        }
        return;
    }

    // Less than
    if (tree->left == NULL)
    {
        tree->left = New(BinaryTreeNode);
        tree->left->id = id;
        tree->left->left = NULL;
        tree->left->left = NULL;
        tree->left->key = NewArray(char, strlen(key));
        strcpy(tree->left->key, key);

        if (value != NULL)
        {

            tree->left->value = NewArray(char, strlen(key));
            strcpy(tree->left->value, value);
        }
        else
        {
            tree->left->value = NULL;
        }
    }
    else
    {
        Insert(tree->left, id, key, value);
    }
    return;
}

static char *Find(BinaryTreeNode *tree, long id)
{
    if (id == tree->id)
    {
        return tree->value;
    }

    if (tree->right != NULL && id > tree->id)
    {
        return Find(tree->right, id);
    }

    if (tree->left != NULL && id < tree->id)
    {
        return Find(tree->left, id);
    }
    return NULL;
}

static int Count(BinaryTreeNode *tree, int *counter)
{
    ++(*counter);

    if (tree->right != NULL)
    {
        Count(tree->right, counter);
    }
    if (tree->left != NULL)
    {
        Count(tree->left, counter);
    }
    return *counter;
}

static void GetKeys(BinaryTreeNode *tree, char **keys, int *index)
{
    keys[*index] = NewArray(char, strlen(tree->key));
    strcpy(keys[*index], tree->key);
    ++(*index);

    if (tree->right != NULL)
    {
        GetKeys(tree->right, keys, index);
    }
    if (tree->left != NULL)
    {
        GetKeys(tree->left, keys, index);
    }
}

static void GetValues(BinaryTreeNode *tree, char **values, int *index)
{
    values[*index] = NewArray(char, strlen(tree->value));
    strcpy(values[*index], tree->value);
    ++(*index);

    if (tree->right != NULL)
    {
        GetValues(tree->right, values, index);
    }
    if (tree->left != NULL)
    {
        GetValues(tree->left, values, index);
    }
}

/* PUBLIC */

BinaryTreeNode *CreateBinaryTree(const char *key, const char *value)
{
    if (key == NULL)
    {
        return NULL;
    }
    BinaryTreeNode *result = New(BinaryTreeNode);
    result->id = Hash(key);
    result->key = NewArray(char, strlen(key));
    strcpy(result->key, key);

    if (value != NULL)
    {
        result->value = NewArray(char, strlen(value));
        strcpy(result->value, value);
    }
    result->left = NULL;
    result->right = NULL;
    return result;
}

BinaryTreeNode *CreateBinaryTreeFrom(int lenght, KeyValuePair *pairs)
{
    if (lenght < 1 ||
        pairs == NULL ||
        pairs[0].value == NULL)
    {
        return NULL;
    }
    BinaryTreeNode *result = CreateBinaryTree(pairs[0].key, pairs[0].value);

    for (int i = 1; i < lenght; ++i)
    {
        if (pairs[i].value != NULL)
        {

            Insert(result, Hash(pairs[i].key), pairs[i].key, pairs[i].value);
        }
    }
    return result;
}

void PutBinaryTreeNode(BinaryTreeNode *tree, const char *key, const char *value)
{
    if (tree == NULL || key == NULL)
    {
        return;
    }
    Insert(tree, Hash(key), key, value);
}

char *GetBinaryTreeNode(BinaryTreeNode *tree, const char *key)
{
    if (tree == NULL || key == NULL)
    {
        return NULL;
    }
    return Find(tree, Hash(key));
}

int CountBinaryTreeNodes(BinaryTreeNode *tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    int counter = 0;
    return Count(tree, &counter);
}

char **GetBinaryTreeKeys(BinaryTreeNode *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }
    char **keys = NewArray(char *, CountBinaryTreeNodes(tree));
    int index = 0;
    GetKeys(tree, keys, &index);
    return keys;
}

char **GetBinaryTreeValues(BinaryTreeNode *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }
    char **values = NewArray(char *, CountBinaryTreeNodes(tree));
    int index = 0;
    GetValues(tree, values, &index);
    return values;
}

int StoreBinaryTree(const char *filename, BinaryTreeNode *tree)
{
    return 0;
}

BinaryTreeNode *LoadBinaryTree(const char *filename)
{
    return NULL;
}
