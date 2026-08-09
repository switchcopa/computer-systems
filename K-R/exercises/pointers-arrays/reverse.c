#include <string.h>

/* reverse: reverse string in place, pointer version*/
void reverse(char *s);
void swap(char *a, char *b);

void swap(char *a, char *b) {
        char temp = *a;
        *a = *b;
        *b = temp;
}

void reverse(char *s) {
        int i;
        size_t len = strlen(s);
        for (i = 0; i < len/2; i++) 
                swap(&s[i], &s[len-i-1]);
}