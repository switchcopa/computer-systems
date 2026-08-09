#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1000

char line[MAX_LINE];
int lim;

int get_line(char destination[]);
bool is_uppercase(char c);
bool is_lowercase(char c);
char upper(char c);
char* scream(char text[]);

int main(void) {
    int c; 
    int len; 

    while ((len = get_line(line)) > 0) {
        char* buffer = scream(line);

        printf("%s\n", buffer);
        free(buffer);
    }

    return 0;
}

int get_line(char destination[]) {
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

bool is_uppercase(char c) {
    return 65 <= c && c <= 90;
}

bool is_lowercase(char c) {
    return 97 <= c && c <= 122;    
}

char upper(char c) {
    return c - 32;
}

char* scream(char text[]) {
    int i;
    int lensize;

    lensize = strlen(text);
    char *buffer = malloc(lensize + 1);

    if (!buffer) {
        perror("failed to allocate memory for buffer\n");
        exit(1);
    }
    
    for (i = 0; i < lensize; i++) {
        if (is_lowercase(text[i])) text[i] = upper(text[i]);

        buffer[i] = text[i];
    }
    
    buffer[i] = '\0';
    return buffer;
}
