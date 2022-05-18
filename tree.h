#ifndef TREE_H
#define THEE_H

typedef struct Node {
    int key;
    int info;
    struct Node *node;
    struct Node *left;
    struct Node *right;
    struct Node *par;
    struct Node *next;
} Node;

typedef struct Tree {
    Node *root;
    int tsize;
} Tree;

#endif
