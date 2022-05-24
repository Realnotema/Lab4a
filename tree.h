#ifndef TREE_H
#define TREE_H

typedef struct Item {
    int info;
    struct Item *next;
} Item;

typedef struct Node {
    int key;
    Item info;
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
