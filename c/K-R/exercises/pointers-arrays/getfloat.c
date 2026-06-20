#include <stdio.h>
#include <float.h>
#include <ctype.h>

#define BUF_SIZE 100

int getfloat(float *);
int getch(void);
void ungetch(int);

char buf[BUF_SIZE];
int bufp = 0;

int main(void) {
	float f;
	int res = getfloat(&f);
	printf("%.6f\n", f);

	return 0;
}

int getfloat(float *fp) {
	if (fp == NULL)
		return 0;

	int c, sign;
	while (isspace(c = getch()))
		;

	if (!isdigit(c) && c != '.' && c != '-' && c != '+') {
		ungetch(c);
		return 0;
	}
        if (c == '+' || c == '-') {
	        sign = (c == '-') ? -1 : 1;
                c = getch();
        } else
                sign = 1;

	for (*fp = 0; isdigit(c); c = getch())
		*fp = *fp * 10 + (c - '0');
	
	if (c != '.') {
		ungetch(c);
		*fp *= sign;
		return c;
	}
        
        float frac = 0.0f, factor = 0.1f;
        while (isdigit(c = getch())) {
                frac += (c - '0') * factor;
                factor *= 0.1f;
        }
        *fp += frac;
        *fp *= sign;

	if (c != EOF)
		ungetch(c);
	return c;
}

int getch(void) {
	return (bufp > 0) ? buf[bufp--] : getchar();
}

void ungetch(int c) {
	if (bufp >= BUF_SIZE)
		return;
	else
		buf[bufp++] = c;	
}
