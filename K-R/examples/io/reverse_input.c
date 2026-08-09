#include <stdio.h> 
#include <stdint.h> 

#define MAX_LINE 1000

uint16_t getline(char line[], uint16_t max_size);
void reverse(char s[], char to[], uint16_t size);

int main() {
    uint16_t len;
    char line[MAX_LINE];
    char to[MAX_LINE];

    while ((len = getline(line, MAX_LINE)) > 0) {
        reverse(line, to, len);

        printf("%s\n", to);
    }

    return 0;
}

uint16_t getline(char line[], uint16_t max_size) {
    int c;
    uint16_t size;

    size = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n' && size < max_size - 1) {
            line[size++] = '\n';
            break;
        }

        if (size < max_size - 1) 
            line[size] = c;

        size++;
    }

    if (size >= max_size) size = max_size - 1;
    line[size] = '\0';

    return size;
}

void reverse(char s[], char to[], uint16_t size) {
    int i, ptr = 0;
    int end = (s[size - 1] == '\n') ? size - 2 : size - 1;

    for (i = end; i >= 0; i--) {
        to[ptr++] = s[i];
    }

    if (s[size - 1] == '\n') {
        to[ptr++] = '\n';
    }

    to[ptr] = '\0';
}
