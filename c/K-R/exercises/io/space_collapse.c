#include <stdio.h>
#include <stdbool.h>

int main() {
    int c;
    bool isLastSpace;
    
    isLastSpace = false; 
    while ((c = getchar()) != EOF) {
        if (c == ' ' && isLastSpace) continue;

        if (c == ' ') isLastSpace = true;
        else isLastSpace = false;

        putchar(c);
    }
    
    printf("Signal EOF\n");

    return 0;
}
