#include <stdio.h> 
#include <stdint.h> 

#define MIN_LINE 80
#define MAX_LINE 1000

uint16_t getline(char destination[]);
void copy(char from[], char to[]);

int main() {
    uint16_t len;
    char line[MAX_LINE];
    
    while ((len = getline(line)) > 0) {
        if (len > MIN_LINE) {
            printf("%s\n", line);
        }
    }

    return 0;
}

uint16_t getline(char destination[]) {
    int c;
    uint16_t nchars;
    
    nchars = 0;
    while (((c = getchar()) != EOF) && (c != '\n')) {
        if (nchars < MAX_LINE - 1) {
            destination[nchars] = c;
        }

        nchars++;
    }
    
    if (nchars < MAX_LINE - 1) {
        destination[nchars] = '\0';
    }
    else destination[MAX_LINE - 1] = '\0';

    return nchars;
}
