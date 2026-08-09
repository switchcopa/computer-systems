#include <stdio.h> 

#define LINE_SIZE 100

int strindex(const char *line_buffer, const char *target);
int get_line(char *buffer, unsigned int max_size);

const char *pattern = "hello";

int main(void) {
        char line_buffer[LINE_SIZE];

        while (get_line(line_buffer, LINE_SIZE) >= 0) {
                int i = strindex(line_buffer, pattern);
        
                if (i == -1)
                        printf("pattern '%s' not found\n", pattern);
                else
                        printf("found pattern in index: %d\n", i);
        }

        return 0;
}

int strindex(const char *line_buffer, const char* target) {
        int i, j, k;

        for (i = 0; line_buffer[i] != '\n' && line_buffer[i] != '\0'; i++) {
                for (j = i, k = 0; line_buffer[j] == target[k]; j++, k++)
                        ;

                if (target[k] == '\0')
                        return i;
        }

        return -1;
}

int get_line(char *buffer, unsigned int max_size) {
        int c;
        unsigned int len = 0;

        while (len < max_size - 1 && (c = getchar()) != EOF) {
                buffer[len++] = c;

                if (c == '\n')
                        break;
        }

        if (c == EOF && len == 0)
                return -1;

        buffer[len] = '\0';
        return len;
}
