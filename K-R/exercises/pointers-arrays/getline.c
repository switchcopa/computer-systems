#include <stdio.h>

#define MAXLINE 1000

size_t get_line(char *line, size_t max_line) {
        int c;
        size_t len = 0;
        
        while (len < max_line - 1 && (c = getchar()) != EOF) {
                if (c == '\n') {
                        line[len++] = c;
                        break;
                }

                line[len++] = c;
        }

        line[len] = '\0';
        return len;
}
