/*
this is a multi line comment!
*/
/* this is also a multi line comment! */
#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>

#define MAXSIZE 2000

char input[MAXSIZE];
const char* filename = "myfile.c";

typedef enum {
    IS_NONE,
    IS_COMMENT,
    IS_MULTI_LINE_COMMENT
} State;

void getinput();
void save_buffer_to_file(const char* filename);

int main(void) {
    getinput();    
    save_buffer_to_file(filename);
    return 0;
}

void getinput() {
    int c, prev;
    State state; 
    uint16_t size;
    
    size = prev = 0;
    state = IS_NONE;
    while ((c = getchar()) != EOF) {
        if (prev == '/' && c == '/') {
            state = IS_COMMENT;
            size--; 
        }

        else if (prev == '/' && c == '*') {
            state = IS_MULTI_LINE_COMMENT;
            size--;
        }
        
        else if (prev == '*' && c == '/' && state == IS_MULTI_LINE_COMMENT) { // this is also a comment
            state = IS_NONE;
            prev = c;
            continue;
        }

        if (state == IS_NONE) input[size++] = c;
        if (c == '\n' && state != IS_MULTI_LINE_COMMENT) {
            state = IS_NONE;
            prev = c;
            continue;
        }

        prev = c;
    }
}

void save_buffer_to_file(const char* filename) {
    FILE* fp = fopen(filename, "w"); 
    if (!fp) {
        perror("Failed to open file\n");
        exit(1);
    }

    fputs(input, fp);
    fclose(fp);
}
