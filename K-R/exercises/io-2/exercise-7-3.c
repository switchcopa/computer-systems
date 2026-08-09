#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

void minprintf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;

    int ival;
    double dval;
    unsigned uval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        } 

        switch (*++p) {
        case 'd':
        case 'i':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
            break;
        case 'u':
            uval = va_arg(ap, unsigned);
            printf("%u", uval);
            break;
        case 'o':
            uval = va_arg(ap, unsigned);
            printf("%o", uval);
            break;
        case 'x':
        case 'X':
            uval = va_arg(ap, unsigned);
            printf("%x", uval);
            break;
        case 'e':
        case 'E':
            dval = va_arg(ap, double);
            printf("%e", dval);
            break;
        default:
            putchar(*p);
            break;
        }
    
        va_end(ap);
    }
}
