#include <ctype.h> 
#include <stdio.h>

int getch(void);
void ungetch(int);

/* getint: get next integer from input to *pn */
int getint(int *pn) {
        int c, sign, d;

        while (isspace(c = getch()))
                ;
        if (!isdigit(c) && c != EOF && c != '-' && c != '+') {
                ungetch(c);
                return 0; 
        }
        
        sign = (c == '-') ? -1 : 1;
        if (c == '-' || c == '+') {
                d = getch();
                if (!isdigit(d)) {
                        ungetch(d);
                        ungetch(c);
                        return 0;
                }

                c = d;
        }
        
        for (*pn = 0; isdigit(c), c = getch();)
             *pn = 10 * *pn + (c - '0');

        *pn *= sign;
        if (c != EOF)
                ungetch(c);

        return c;
}
