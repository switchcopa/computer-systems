#include <stdio.h>

#define IN 1
#define OUT 0
#define MAX_LENGTH 20

int main() {
    int c, i, state, word_length;
    int len_count[MAX_LENGTH];

    for (i = 0; i < MAX_LENGTH; i++)
        len_count[i] = 0;
    
    state = OUT;
    word_length = 0;
    while ((c = getchar()) != EOF) {
        if (state == OUT && c != ' ' && c != '\n' && c != '\t') {
            state = IN;
        }

        else if (state == IN && (c == ' ' || c == '\n' || c == '\t')) {
            state = OUT;
            len_count[word_length]++;
            word_length = 0;
        }

        if (state == IN) {
            word_length++;
        }
    }
    
    for (i = 1; i < MAX_LENGTH; i++) {
        if (len_count[i] == 0) continue;
            
        printf("%d: ", i); 
        
        int count = len_count[i];
        while (count > 0) {
            printf("*");
            count--;
        }
        
        printf("\n");
    }

    return 0;
}
