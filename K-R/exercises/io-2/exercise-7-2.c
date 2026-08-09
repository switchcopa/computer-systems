#include <stdio.h>
#include <ctype.h>

#define PRINT_COLUMN_LINE_BREAKS 20

int main(int argc, char **argv) {
    int c;
    unsigned col = 0;

    while ((c = getchar()) != EOF) {
        if (col == PRINT_COLUMN_LINE_BREAKS - 1) {
            putchar('\n');
            col = 0;
        }
        
        if (isprint(c))
           putchar(c);
        else
           printf("\\x%02x", c);

        col++;
    }

    return 0;
}
