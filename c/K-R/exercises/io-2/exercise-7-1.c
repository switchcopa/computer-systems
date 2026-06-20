#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LINESIZE 1000

int getline(char *buf, int mode, int max);

int main(int argc, char **argv) {
    if (argc != 1) {
        fprintf(stderr, "Usage: ./lower or ./upper\n");
        return -1;
    }
    
    char line[LINESIZE];
    int len;
    int mode;
    
    if (strcmp(argv[0], "./lower") == 0) mode = 0;
    else if (strcmp(argv[0], "./upper") == 0) mode = 1;
    else {
        fprintf(stderr, "Unknown name %s\n", argv[0]);
        return -1;
    }

    while ((len = getline(line, mode, LINESIZE)) > 0)
        printf("%s", line);

    return 0;
}

int getline(char *buf, int mode, int max) {
    int c;
    int len = 0;
    int (*fp)(int) = (mode == 0) ? tolower : toupper;

    while ((c = getchar()) != EOF && len < max - 1) {
        if (c == '\n') {
            buf[len++] = '\n';
            break;
        }
        
        buf[len++] = fp(c);    
    }
     
    if (c == EOF && len == 0)
        return EOF;

    buf[len] = '\0';
    return len;
}
