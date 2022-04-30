#include <stdio.h>

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

int Menu (int choose) {
        switch (choose) {
                case 1:
                        break;
                case 2:
                        break;
                case 3:
                        break;
                case 4:
                        break;
                case 5:
                        break;
                case 6:
                        break;
                case 7:
                        break;
                case 8:
                        break;
                case 9:
                        return 1;
        }
}

int main() {
        int flag = 0;
        const char *options[] = {"1. Add element", "2. Delete element", "3. Tree traversal", "4. Find element by key", "5. Special find", "6. Print tree", "7. Timing", "8. Open file", "9. Quit"};
        do {
                flag = Menu(Dialog(options, 9));
        } while (flag == 0);
        return 0;
}
