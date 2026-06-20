#include <ctype.h>
#include <stdio.h>

int atoi(const char *nptr);

int main(void) {
        int n = atoi("-1341");
        printf("%d\n", n);

        return 0;
}

/* atoi: convert ASCII string that contains numbers to an integer */
int atoi(const char *nptr) {
        while (isspace(*nptr))
                nptr++;

        int sign, n;
        
        if (*nptr == '-') {
                sign = -1;
                nptr++;
        } else if (*nptr == '+') {
                sign = 1;
                nptr++;
        } else sign = 1;
        
        n = 0;
        while (isdigit(*nptr)) {
                n = n * 10 + (*nptr - '0');
                nptr++;
        }

        return sign * n;
}
