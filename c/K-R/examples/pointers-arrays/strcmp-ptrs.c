#include <stdio.h>

/* strcmp: return < 0 if s < t, 0 if s == t and > 0 if s > t */
int strcmp(const char* s, const char *t) {
        for (; *s == *t; s++, t++)
                if (*s == '\0')
                        return 0;

        return *s - *t;
}

int main(void) {
        const char *s = "ab";
        const char *t = "ab";
        
        int val = strcmp(s, t);
        if (val > 0)
                printf("s is larger than t\n");
        else if (val < 0)
                printf("s is smaller than t\n");
        else 
                printf("s is the same as t\n");
        return 0;
}
