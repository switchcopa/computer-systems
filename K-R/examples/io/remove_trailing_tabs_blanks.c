#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_SIZE 1000
const bool SHOULD_REMOVE_TRAILING = true;
const bool SHOULD_NOT_REMOVE_TRAILING = false;

uint16_t getline(char destination[], uint16_t max_size);
void remove_trailing(char s[], char to[], uint16_t size); 

int main() {
    uint16_t len;
    char line[MAX_SIZE]; 
    char to[MAX_SIZE];

    while ((len = getline(line, MAX_SIZE)) > 0) {
        remove_trailing(line, to, len);

        if (len > 0) {
            printf("%s", to);
        }
    }

    return 0;
}

uint16_t getline(char destination[], uint16_t max_size) { 
    int c;
    uint16_t size;
    
    size = 0;
    while ((c = getchar()) != EOF ) {
        if (c == '\n' && size < max_size - 1) {
            destination[size++] = '\n';
            break;
        }

        if (size < max_size - 1) {
            destination[size] = c;
        }

        size++;
    }
    
    if (size >= max_size) size = max_size - 1;
    destination[size] = '\0';

    return size;
}

void remove_trailing(char s[], char to[], uint16_t size) {
    uint16_t i, ptr;
    bool status;
    
    status = SHOULD_NOT_REMOVE_TRAILING;
    for (i = ptr = 0; (s[i] != '\0' || s[i] != '\n') && i < size; i++) {
        if (s[i] == ' ' && s[i+1] == ' ') status = SHOULD_REMOVE_TRAILING;
        else status = SHOULD_NOT_REMOVE_TRAILING;

        if (status == SHOULD_REMOVE_TRAILING) continue;
        else to[ptr++] = s[i];
    }
    
    to[ptr++] = '\n';
    to[ptr] = '\0';
}
