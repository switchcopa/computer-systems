#include <stdio.h>

int main() {
    int tabs, newlines, blanks;
    int c; 

    tabs = 0;
    newlines = 0;
    blanks = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\t') tabs++;
        else if (c == '\n') newlines++;
        else if (c == ' ') blanks++;
    }
    
    printf("There are %d tabs, %d new lines, and %d blanks", tabs, newlines, blanks);

    return 0;
}
