
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btree.h"
#include "util.h"

static size_t Hash(const char *key)
{
    if (key == NULL)
    {
        return 0;
    }

    size_t hash = 0;
    int index = 0;

    while (key[index] != '\0')
    {
        hash += 31 * hash + key[index];
        ++index;
    }
    return hash;
}

static void Insert(BinaryTreeNode *tree, size_t id, const char *key, const char *value)
{
    // Equal
    if (id == tree->id)
    {
        Delete(tree->value);

        if (value != NULL)
        {
            size_t len = strlen(value);
            tree->value = NewArray(char, len);
            memcpy_s(tree->value, len, value, len);
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

            size_t len = strlen(key);
            tree->right->key = NewArray(char, len);
            memcpy_s(tree->right->key, len, key, len);

            if (value != NULL)
            {
                size_t l = strlen(value);
                tree->right->value = NewArray(char, l);
                memcpy_s(tree->right->value, l, value, l);
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

        size_t len = strlen(key);
        tree->left->key = NewArray(char, len);
        memcpy_s(tree->left->key, len, key, len);

        if (value != NULL)
        {
            size_t l = strlen(value);
            tree->left->value = NewArray(char, l);
            memcpy_s(tree->left->value, l, value, l);
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

static char *Find(BinaryTreeNode *tree, size_t id)
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
    size_t len = strlen(tree->key);
    keys[*index] = NewArray(char, len);
    memcpy_s(keys[*index], len, tree->key, len);
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
    size_t len = strlen(tree->value);
    values[*index] = NewArray(char, len);
    memcpy_s(values[*index], len, tree->value, len);
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

static void Store(FILE *file, BinaryTreeNode *tree)
{
    static size_t zerolen = 0;
    fwrite(&tree->id, sizeof(size_t), 1, file);
    size_t keylen = strlen(tree->key);
    fwrite(&keylen, sizeof(size_t), 1, file);
    fwrite(tree->key, sizeof(char), keylen, file);

    if (tree->value != NULL)
    {
        size_t valuelen = strlen(tree->value);
        fwrite(&valuelen, sizeof(size_t), 1, file);
        fwrite(tree->value, sizeof(char), valuelen, file);
    }
    else
    {

        fwrite(&zerolen, sizeof(size_t), 1, file);
    }
    if (tree->right != NULL)
    {
        Store(file, tree->right);
    }
    if (tree->left != NULL)
    {
        Store(file, tree->left);
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
    size_t len = strlen(key);
    result->key = NewArray(char, len);
    memcpy_s(result->key, len, key, len);

    if (value != NULL)
    {
        size_t l = strlen(value);
        result->value = NewArray(char, l);
        memcpy_s(result->value, l, value, l);
    }
    result->left = NULL;
    result->right = NULL;
    return result;
}

BinaryTreeNode *CreateBinaryTreeFrom(int lenght, KeyValuePair *pairs)
{
    if (lenght < 1 || pairs == NULL || pairs[0].value == NULL)
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

char *GetBinaryTreeValue(BinaryTreeNode *tree, const char *key)
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
    if (tree == NULL || filename == NULL || strlen(filename) <= 0)
    {
        return 0;
    }
    FILE *file;
    fopen_s(&file, filename, "wb");

    if (!file)
    {
        return 0;
    }
    Store(file, tree);
    fclose(file);
    return 1;
}

BinaryTreeNode *LoadBinaryTree(const char *filename)
{
    if (filename == NULL || strlen(filename) <= 0)
    {
        return NULL;
    }
    FILE *file;
    fopen_s(&file, filename, "rb");

    if (!file)
    {
        return NULL;
    }
    BinaryTreeNode *head = New(BinaryTreeNode);
    head->left = NULL;
    head->right = NULL;
    size_t id;
    size_t keylen;
    char *key;
    size_t valuelen;
    char *value;
    int success;

    if (!fread(&head->id, sizeof(size_t), 1, file))
    {
        Delete(head);
        fclose(file);
        return NULL;
    }
    if (!fread(&keylen, sizeof(size_t), 1, file))
    {
        Delete(head);
        fclose(file);
        return NULL;
    }
    head->key = NewArray(char, keylen + 1);
    if (fread(head->key, sizeof(char), keylen, file) != keylen)
    {
        Delete(head->key);
        Delete(head);
        fclose(file);
        return NULL;
    }
    head->key[keylen] = '\0';

    if (!fread(&valuelen, sizeof(size_t), 1, file))
    {
        Delete(head->key);
        Delete(head);
        fclose(file);
        return NULL;
    }
    if (valuelen > 0)
    {
        head->value = NewArray(char, valuelen + 1);

        if (fread(head->value, sizeof(char), valuelen, file) != valuelen)
        {
            Delete(head->key);
            Delete(head->value);
            Delete(head);
            fclose(file);
            return NULL;
        }
        head->value[valuelen] = '\0';
    }
    else
    {
        head->value = NULL;
    }
    success = 1;

    while (success)
    {
        if (!fread(&id, sizeof(size_t), 1, file))
        {
            success = 0;
            continue;
        }
        if (!fread(&keylen, sizeof(size_t), 1, file))
        {
            success = 0;
            continue;
        }
        key = NewArray(char, keylen + 1);
        if (!key)
        {
            success = 0;
            continue;
        }
        if (fread(key, sizeof(char), keylen, file) != keylen)
        {
            Delete(key);
            success = 0;
            continue;
        }
        key[keylen] = '\0';
        if (!fread(&valuelen, sizeof(size_t), 1, file))
        {
            Delete(key);
            success = 0;
            continue;
        }
        if (valuelen > 0)
        {
            value = NewArray(char, valuelen + 1);
            if (!value)
            {
                Delete(key);
                success = 0;
                continue;
            }
            if (fread(value, sizeof(char), valuelen, file) != valuelen)
            {
                Delete(key);
                Delete(value);
                success = 0;
                continue;
            }
            value[valuelen] = '\0';
        }
        else
        {
            value = NULL;
        }
        Insert(head, id, key, value);
        Delete(key);
        Delete(value);
    }

    fclose(file);
    return head;
}
