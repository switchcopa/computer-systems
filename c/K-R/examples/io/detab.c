#include <stdio.h>

#define TAB_SIZE 2

int main(void) {
    int c;
    int column;

    column = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int spaces = TAB_SIZE - (column % TAB_SIZE);
            for (int i = 0; i < spaces; i++) {
                putchar(' ');
                column++;
            }
        }

        else if (c == '\n') {
            putchar(c);
            column = 0;
        }

        else {
            putchar(c);
            column++;
        }
    }

    return 0;
}
