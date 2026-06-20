/* Ex 8-1 cat2.c : concatenate files
 * using functions from the UNIX 
 * system calls.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <syscalls.h>

#define PERMS 0666

void error(char *fmt, ...);

int main(int argc, char **argv)
{
    char buf[BUFSIZ];
    int n;
    int fp;

    if (argc == 1)
        while ((n = read(0, buf, BUFSIZ)) > 0)
            write(1, buf, n);
    else
        while (--argc > 0)
        {
            if ((fp = open(argv[argc], O_RDONLY, 0)) < 0)
                error("failed to open file %s", argv[argc]);
            if ((n = read(fp, buf, BUFSIZ)) < 0)
                error("error occurred while reading file %s", argv[argc]);
            write(1, buf, n);
        }

    exit(EXIT_SUCCESS);
}

void error(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);

    exit(EXIT_FAILURE);
}
