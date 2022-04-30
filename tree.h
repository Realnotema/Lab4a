#ifndef TREE_H
#define THEE_H

typedef struct Node {
        int key;
        int info;
        struct Node *left;
        struct Node *right;
        struct Node *parent;
        struct Node *next;
} Node;

typedef struct Tree {
        Node *root;
} Tree;

#endif
