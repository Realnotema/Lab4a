#include <stdio.h>
#include "tree.h"
#include <stdlib.h>

int processWriteTree (FILE *fb, Node *root, int headKey, int p) {
    if (root->left)
        processWriteTree(fb, root->left, headKey, p + 5);
    if (root->key != headKey) {
        fwrite(&root->key, sizeof(int), 1, fb);
        fwrite(&root->info, sizeof(int), 1, fb);
    }
    if (root->right)
        processWriteTree(fb, root->right, headKey, p + 5);
}

int writeTree (FILE *fb, Tree *tree) {
    if (tree == 0)
        return 1;
    fwrite(&tree->tsize, sizeof(int), 1, fb);
    fwrite(&tree->root->key, sizeof(int), 1, fb);
    fwrite(&tree->root->info, sizeof(int), 1, fb);
    processWriteTree(fb, tree->root, tree->root->key, 0);
    return 0;
}

int addElement (Tree *tree, int key, int info) {
    Node *temp = (Node *) calloc(1, sizeof(Node));
    temp->key = key;
    temp->info.info = info;
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
    if (temp->key == par->key) {
        while (par->info.next != NULL)
            par = par->info.next;
        par->info.next = temp;
        return 0;
    }
    if (temp->key < par->key)
        par->left = temp;
    else {
        par->right = temp;
        temp->next = par->par;
    }
    temp->par = par;
    tree->tsize++;
    return 0;
}

int readTree (FILE *fb, Tree *tree) {
    int key, info;
    if (tree == 0 || fb == 0)
        return 1;
    fread(&tree->tsize, sizeof(int), 1, fb);
    for (int i = 0; i <= tree->tsize; i++) {
        fread(&key, sizeof(int), 1, fb);
        fread(&info, sizeof(int), 1, fb);
        addElement(tree, key, info);
    }
    return 0;
}

Node *traversal (Tree *tree, Node *ptr) {
    if (ptr == NULL) {
        ptr = tree->root->left;
        while (ptr->left != NULL)
            ptr = ptr->left;
        return ptr;
    }
    if (ptr == tree->root) {
        ptr = tree->root->right;
        while (ptr->left != NULL)
            ptr = ptr->left;
        return ptr;
    }
    if (ptr->right != NULL) {
        ptr = ptr->right;
        return ptr;
    }
    if (ptr->right == NULL && ptr->next == NULL) {
        ptr = ptr->par;
        return ptr;
    }
    if (ptr->next != NULL)
        ptr = ptr->next;
    return ptr;
}

int findByKey (Tree *tree, int key) {
    Node *pos = NULL;
    for (int i = 0; i <= tree->tsize; i++) {
        pos = traversal(tree, pos);
        if (i == tree->tsize)
            return 1;
        if (pos->key == key && pos->node != NULL) {
            do {
                printf("(%d) %d\n", pos->key, pos->info);
                pos = pos->node;
            } while (pos->node != NULL);
        }
        if (pos->key == key) {
            printf("(%d) %d", pos->key, pos->info);
            return 0;
        }
    }
    return 0;
}

Node *findMax (Node *ptr) {
    while (ptr->right != NULL)
        ptr = ptr->right;
    return ptr;
}

int delElement (Tree *tree, Node *ptr, int key) {
    Node *pos = NULL;
    for (int i = 0; i <= tree->tsize; i++) {
        pos = traversal(tree, pos);
        if (pos->key == key)
            break;
    }
    if (pos->key != key)
        return 1;
    if (pos->info.next != NULL) {
        while (pos->info.next != NULL)
            pos = pos->info.next;
        free(pos);
        tree->tsize--;
        return 0;
    }
    if (pos->left && pos->right) {
        Node *max = findMax(pos->left);
        pos->info = max->info;
        delElement(tree, max, key);
        return 0;
    } else if (pos->left) {
        if (pos == pos->par->left) {
            pos->par->left = pos->left;
        } else {
            pos->par->right = pos->left;
        }
    } else if (pos->right) {
        if (pos == pos->par->right) {
            pos->par->right = pos->right;
            } else {
            pos->par->left = pos->right;
            }
    } else {
        if (pos == pos->par->left) {
            pos->par->left = NULL;
        } else {
            pos->par->right = NULL;
        }
    }
    free(pos);
    tree->tsize--;
    return 0;
}

Node *special (Tree *tree) {
    if (tree == NULL)
        return 1;
    Node *ptr = tree->root->left;
    while (ptr->left != NULL)
        ptr = ptr->left;
    return ptr;
}

int freeTree (Node *root) {
    if (root == NULL)
        return 0;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
    return 0;
}

int printTree (Node *root, int p) {
    if (root->left)
        printTree(root->left, p + 5);
    for (int i = 0; i <= p; i++)
        printf(" ");
    if (root->info.next == NULL) {
        printf("(%d)\n", root->key);
    } else {
        printf("(%d) %d ", root->key, root->info.info);
        while (root->info.next) {
            root = root->info.next;
            printf("-> %d", root->info.info);
        }
        printf("\n");
    }
    if (root->right)
        printTree(root->right, p + 5);
}
