#include <stdlib.h>

/* strncpy: copy at most n bytes from src to dest */
void strn_cpy(char *dest, const char* src, size_t n) {
        size_t i;
        
        for (i = 0; i < n && src[i] != '\0'; i++)
                dest[i] = src[i];

        if (i < n)
                dest[i] = '\0';
}

/* strncat: add n bytes from the string src to the end of the dest */
void strn_cat(char *dest, const char* src, size_t n) {
        while (*dest != '\0')
                dest++;

        size_t i;
        i = 0;
        for (; i < n && src[i] != '\0'; i++)
                dest[i] = src[i];

        dest[i] = '\0';
}

/* strncmp: compare n bytes from s and t */
int strn_cmp(const char *s, const char *t, size_t n) {
        size_t i;

        for (i = 0; i < n && s[i] != '\0'; i++)
                if (s[i] != t[i])
                        return 0;

        return 1;
}
