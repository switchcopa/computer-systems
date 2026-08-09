#include <stdio.h> 
#include <stdint.h>

#define MAX_LINE 1000

uint16_t getline(char destnation[], uint16_t max_size);
void copy(char from[], char to[]);

int main() {
    uint16_t len; 
    uint16_t max;
    char line[MAX_LINE];
    char longest[MAX_LINE];

    max = 0;
    while ((len = getline(line, MAX_LINE)) > 0) {
        if (len > max) {
            max = len;
            copy(line, longest);
        }
    }
    
    if (max > 0) {
        printf("%s", longest);
    }
    return 0;
}

uint16_t getline(char destination[], uint16_t max_size) {
    int c ;
    uint16_t nchars; 

    nchars = 0;
    while ((c = getchar()) != EOF && (c != '\n')) {
        if (nchars < max_size - 1) {
            destination[nchars] = c;
        }
        
        nchars++;
    }
    
    destination[max_size - 1] = '\0';
    return nchars;
}

void copy(char from[], char to[]) {
    int i, c;

    for (i = 0; from[i] != '\0'; i++) {
        c = from[i];
        to[i] = c;
    }

    to[i] = '\0';
}
