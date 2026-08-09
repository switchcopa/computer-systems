#include <stdio.h>

#define MAX_LINES 1000
#define OUT_LINE 0
#define IN_LINE 1

int main() {
    int c, status, char_count, longest_character_lines, longest_line, curr_line;
    
    status = OUT_LINE;
    char_count = longest_character_lines = 0;
    longest_line = curr_line = 1;

    while ((c = getchar()) != EOF) {
        if (status == OUT_LINE && c != '\n') 
            status = IN_LINE;

        if (status == IN_LINE && c == '\n') {
            status = OUT_LINE;
            if (longest_character_lines < char_count) {
                longest_character_lines = char_count;
                longest_line = curr_line;
            }
            char_count = 0;
            curr_line++;
        }

        if (status == IN_LINE) 
            char_count++;
    } 

    printf("The longest line is the %dth line with %d length", longest_line, longest_character_lines);

    return 0;
}
