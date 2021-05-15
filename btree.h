#pragma once

#include <stdlib.h>

// Represents a node of the tree
typedef struct s_BinaryTreeNode {
    size_t id;
    char* key;
    char* value;
    struct s_BinaryTreeNode* left;
    struct s_BinaryTreeNode* right;
} BinaryTreeNode;

// Represents a key => value pair.
typedef struct
{
    const char* key;
    const char* value;
} KeyValuePair;

// Creates a Binary Tree using key => value specified
BinaryTreeNode* CreateBinaryTree(const char* key, const char* value);

// Creates a Binary Tree using an array of Key => values
BinaryTreeNode* CreateBinaryTreeFrom(int lenght, KeyValuePair* pairs);

// Inserts a key => value into the tree
void PutBinaryTreeNode(BinaryTreeNode* tree, const char* key, const char* value);

// Returns the value of the specified key
char* GetBinaryTreeNode(BinaryTreeNode* tree, const char* key);

// Stores the binary tree in a file
int StoreBinaryTree(const char* filename, BinaryTreeNode* tree);

// Reads a file and returns the binary tree it contains
BinaryTreeNode* LoadBinaryTree(const char* filename);

// Returns the lenght of the binary tree
int CountBinaryTreeNodes(BinaryTreeNode* tree);

// Returns an array of keys
char** GetBinaryTreeKeys(BinaryTreeNode* tree);

// Returns an array of values
char** GetBinaryTreeValues(BinaryTreeNode* tree);
