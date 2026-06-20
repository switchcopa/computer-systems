#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 1000
#define UNSIGNED_BASE_TYPE 10

typedef enum Type
{
    INT_P,
    DOUBLE_P,
    UNSIGNED_P,
    CHAR_P
} Type;

void minscanf(char *fmt, ...);
static void minread(void *dest, Type type);

int main(void)
{
    // all tests were passed
    printf("test 4: char *\n");

    char buf[50];
    minscanf("%s", &buf);
    printf("%s\n", buf);
    return 0;
}

void minscanf(char *fmt, ...)
{
    va_list  ap;

    char     *p, *sval;
    int      *ival;
    double   *dval;
    unsigned *uval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%')
            continue;

        switch (*++p) {
        case 'd':
            ival = va_arg(ap, int *);
            minread(ival, INT_P);
            break;

        case 'f':
            dval = va_arg(ap, double *);
            minread(dval, DOUBLE_P);
            break;

        case 'u':
            uval = va_arg(ap, unsigned *);
            minread(uval, UNSIGNED_P);
            break;

        case 's':
            sval = va_arg(ap, char *);
            minread(sval, CHAR_P);
            break;
        }
    }
}

static void minread(void *dest, Type type)
{
    char buf[BUFSIZE];
    int i = 0;
    int c;
    int sign = 1;

    switch (type) {
        case INT_P:
            while ( isspace((c = getchar())) )
                ;
            if (c == '-') {
                sign = -1;
                c = getchar();
            }

            while ( isdigit(c) ) {
                buf[i++] = c;
                c = getchar();
            }

            buf[i] = '\0';
            *(int *)dest = sign * atoi(buf);
            break;
        case DOUBLE_P:
            while ( isspace((c = getchar())) )
                ;
            if (c == '-') {
                sign = -1;
                c = getchar();
            }
            
            while ( isdigit(c) ) { buf[i++] = c; c = getchar(); }

            if (c == '.') { buf[i++] = c; c = getchar(); }

            while ( isdigit(c) ) { buf[i++] = c; c = getchar(); }

            *(double *)dest = sign * atof(buf);
            break;
        case UNSIGNED_P:
            while ( isspace((c = getchar())) )
                ;

            while ( isdigit(c) ) {
                buf[i++] = c;
                c = getchar();
            }
            
            if (i == 0) {
                *(unsigned *)dest = 0U;
                break;
            }

            buf[i] = '\0';
            char *end;
            *(unsigned *)dest = (unsigned)strtoul(buf, &end, UNSIGNED_BASE_TYPE);
            break;
        case CHAR_P:
            while ((c = getchar()) != EOF && !isspace(c))
                buf[i++] = c;
            buf[i] = '\0';

            char *p = (char *)dest;
            strcpy(p, buf);
            break;
        default: break;
    }
}
