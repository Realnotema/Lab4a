#ifndef PROCESS_H
#define PROCESS_H

int addElement (Tree *tree, int key, int info);
Node *traversal (Tree *tree, Node *ptr);
Node *special (Tree *tree);
int findByKey (Tree *tree, int key);
int delElement (Tree *tree, Node *ptr, int key);
int freeTree (Node *root);
int printTree (Node *root, int p);
int writeTree (FILE *fb, Tree *tree);
int processWriteTree (FILE *fb, Node *root, int headKey, int p);
int writeFrequency (FILE *fb, Tree *tree);
int writeBinaryTree (FILE *fb, Tree *tree);
int readTree (FILE *fb, Tree *tree);

#endif
