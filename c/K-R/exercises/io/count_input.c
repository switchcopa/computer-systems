#include <stdio.h>

#define OUT 0
#define IN 1

/*  
    This program reads input and counts the number of characters, words
    and new lines in our input stream
*/

int main() {
    int c;
    int nw, nc, nl, state;
    
    nw = nc = nl = 0;
    state = OUT;

    while ((c = getchar()) != EOF) {
        nc++;

        if (state == OUT) {
            nw++;
            state = IN;
        }

        if (c == '\n') {
            nl++;
        }

        if ((c == ' ' || c == '\n' || c == '\t') && state == IN) {
            state = OUT;
        }
    }    
    
    printf("SIGNAL EOF\nThere are %d characters, %d words, and %d new lines\n", nc, nw, nl);
    return 0;
}
