#include <stdio.h>
#include <stdbool.h>

void squeeze(char s[], char t[]);

int main(void) {
    char s[] = "hello";
    char t[] = "wrld";

    squeeze(s, t);

    printf("%s\n", s);

    return 0;
}

void squeeze(char s[], char t[]) {
    bool seen[256] = {false};
    int i, c, k;
    
    for (i = 0; (c = (unsigned char) t[i]) != '\0'; i++) 
        seen[c] = true;

    for (i = k = 0; (c = (unsigned char) s[i]) != '\0'; i++) {
        if (!seen[c]) 
            s[k++] = c;
    }

    s[k] = '\0';
}
