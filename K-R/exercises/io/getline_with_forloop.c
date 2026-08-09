#include <stdio.h> 

#define MAX_LINE 1000

char line[MAX_LINE];
int lim;

int getline(char destination[]);

int main(void) {
    int c; 
    int len;
    
    while ((len = getline(line)) > 0) {
        printf("our input string literal with size %d: %s\n", len, line);
    }

    return 0;
}

int getline(char destination[]) {
    int c, i; 
    lim = MAX_LINE - 2;
    
    for (i = 0; i < lim; i++) {
        c = getchar();

        if (c == '\n') break;
        else if (c == EOF) break;
        
        destination[i] = c; 
    }

    destination[i] = '\0'; 

    return i;
}
