#include <stdio.h>

int addElement (Tree *tree, int key, int info) {
        Node *temp = (Node *) calloc(1, sizeof(Node));
        temp->key = key;
        temp->info = info;
        if (tree->root == NULL) {
                tree->root = temp;
                return 0;
        }
        Node *ptr = tree->root;
        Node *par = NULL;
        while (ptr != NULL) {
                par = ptr;
                if (temp->key < ptr->key)
                        ptr = ptr->left;
                else
                        ptr = ptr->right;
        }
        if (temp->key < par->key)
                par->left = temp;
        else
                par->right = temp;
        temp->par = par;
        return 0;
}
