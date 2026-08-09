#include <stdio.h>

int main() {
    int c, nwhite, nother;
    int ndigit[10];

    for (int i = 0; i < 10; i++) 
        ndigit[i] = 0;
    
    while ((c = getchar()) != EOF) {
        if (c >= '0' || c <= '9') {
            ndigit[c - '0']++;
        }

        if (c == ' ' || c == '\n' || c == '\t') 
            nwhite++;

        else nother++;
    }
    
    printf("Digits:");
    for (int i = 0; i < 10; i++) {
        printf(" %d", ndigit[i]);
    }

    printf(", white space: %d", nwhite);
    printf(", nother: %d\n", nother);

    return 0;
}

