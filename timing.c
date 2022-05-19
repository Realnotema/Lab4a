#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"
#include "process.h"

int randTree (Tree *tree, int count, int arr[]) {
    for (int i = 0; i < count; i++) {
        int n = rand()%1000;
        addElement (tree, n, n);
        arr[i] = n;
    }
    return 0;
}

int timingFind (Tree *tree, int key) {
    Node *pos = NULL;
    for (int i = 0; i <= tree->tsize; i++) {
        pos = traversal(tree, pos);
        if (i == tree->tsize)
            return 1;
        if (pos->key == key)
            return 0;
    }
    return 0;
}

int timing (Tree *tree, int n) {
    int randNum = 0;
    clock_t time1;
    FILE *fb = fopen("timing", "w");
    fprintf(fb, "Count\tTime\n");
    for (int i = 1000; i <= 10000; i += 1000) {
        int arr[i];
        double time = 0;
        for (int j = 0; j < 10; j++) {
            switch (n) {
                case 1:
                    time1 = clock();
                    randTree(tree, i, arr);
                    break;
                case 2:
                    randTree(tree, i, arr);
                    time1 = clock();
                    randNum = rand() % (i - 1) + 1;
                    timingFind(tree, arr[randNum]);
                    break;
                case 3:
                    randTree(tree, i, arr);
                    time1 = clock();
                    randNum = rand() % (i - 1) + 1;
                    delElement(tree, arr[randNum]);
                    break;
                case 4:
                    return 0;
            }
            clock_t time2 = clock();
            time += (double) (time2 - time1) / CLOCKS_PER_SEC;
        }
        fprintf(fb, "%d\t%lf\n", i, time / (double) 10);
    }
    fclose(fb);
}
