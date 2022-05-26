#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "process.h"
#include "input.h"

int Dialog(const char *options[], int CountOptions) {
    int choose = 0;
    for (int i = 0; i < CountOptions; i++)
        puts(options[i]);
    char *errmess = "";
    do {
        puts(errmess);
        do {
            choose = GetInt();
        } while (choose > CountOptions || choose < 0);
        if (choose < 0 || choose > CountOptions)
            errmess = "Incorrect input. Try again";
    } while (choose < 0 || choose > CountOptions);
    return choose;
}

int Menu (int choose, Tree *tree) {
    FILE *fo;
    Node *pos = NULL;
    int key = 0;
    int info = 0;
    int flag = 0;
    char *mess[] = {"Enter your key", "Enter info", "No match key"};
    switch (choose) {
        case 1:
            puts(mess[0]);
            key = GetInt();
            puts(mess[1]);
            info = GetInt();
            addElement(tree, key, info);
            break;
        case 2:
            puts(mess[0]);
            key = GetInt();
            delElement (tree, key);
            break;
        case 3:
            for (int i = 0; i <= tree->tsize; i++) {
                pos = traversal(tree, pos);
                printf("%d", pos->key);
            }
            printf("\n");
            break;
        case 4:
            puts(mess[0]);
            key = GetInt();
            flag = findByKey (tree, key);
            if (flag == 1)
                puts(mess[2]);
            printf("\n");
            break;
        case 5:
            pos = special(tree);
            printf("Minimal element = %d\n", pos->key);
            break;
        case 6:
            printTree (tree->root, 0);
            break;
        case 7:
            puts("1. Add Element\n2. Find by key\n3. Delete element");
            timing(tree, GetInt());
            break;
        case 8:
            puts("Enter name of file:");
            fo = fopen(GetStr(), "r+b");
            readTree(fo, tree);
            fclose(fo);
            break;
        case 9:
            return 1;
    }
    return 0;
}

int main() {
    int flag = 0;
    Tree *tree = (Tree *) calloc(1, sizeof(Tree));
    const char *options[] = {"1. Add element", "2. Delete element", "3. Tree traversal", "4. Find element by key", "5. Special find", "6. Print tree", "7. Timing", "8. Open file", "9. Quit"};
    do {
        flag = Menu(Dialog(options, 9), tree);
    } while (flag == 0);
    puts("Enter name of file to save your tree:");
    FILE *fb = fopen(GetStr(), "w");
    writeTree (fb, tree);
    fclose(fb);
    system("dot -Tpng test.dot -o test.png");
    freeTree(tree->root);
    return 0;
}
