
/* Exercise 8-2: Rewrite fopen and _fillbuf with 
 * fields instead of explicit bit operations.
 * Compare code size and execution speed. */

#include "syscalls.h"
#include <stdlib.h>

#define OPEN_MAX 20
#define PERMS 0666
#define EOF (-1)
#define BUFSIZ 8192

#define _READ  01
#define _WRITE 02
#define _UNBUF 04
#define _EOF   010
#define _ERR   020

typedef struct _iobuf
{
    int cnt;
    char *ptr;
    char *base;
    struct {
        unsigned int _read  : 1;
        unsigned int _write : 1;
        unsigned int _unbuf : 1;
        unsigned int _eof   : 1;
        unsigned int _err   : 1;
    } flags;
    int fd;
} FILE;

FILE _iob[OPEN_MAX] = {
    { 0, NULL, NULL, {._read = 1, ._write = 0, ._unbuf = 0,
                      ._eof = 0, ._err = 0}, 0 },

    { 0, NULL, NULL, {._read = 0, ._write = 1, ._unbuf = 0,
                      ._eof = 0, ._err = 0}, 1 },

    { 0, NULL, NULL, {._read = 0, ._write = 1, ._unbuf = 1,
                      ._eof = 0, ._err = 0}, 2 }
};

#define stdin ((FILE)&_iob[0])
#define stdout ((FILE)&_iob[1])
#define stderr ((FILE)&_iob[2])

FILE *fopen(char *name, char *mode);
int _fillbuf(FILE *fp);

/* code seems more than it should be,
 * I prefer explicitely using bit operations
 * rather than bit fields
 * For the time execution difference, using
 * flags is definitely faster and cache friendly,
 * and requires only one CPU instruction,
 * it just looks cleaner in code */

#define getc(p) (--(p)->cnt >= 0 \
            ? (unsigned char) *(p)->ptr++ : _fillbuf(p))


FILE *
fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (!fp->flags._read && !fp->flags._write)
            break;
    if (fp >= _iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a')
    {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r')
        fp->flags._read = 1;
    else
        fp->flags._write = 1;
    return fp; 
}

int
_fillbuf(FILE *fp)
{
    int bufsize;
    if (!fp->flags._read || fp->flags._eof || fp->flags._err)
        return EOF;
    bufsize = (fp->flags._unbuf) ? 1 : BUFSIZ;
    if (fp->base == NULL)
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0)
    {
        if (fp->cnt == -1)
            fp->flags._eof = 1;
        else
            fp->flags._err = 1;
        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char) *fp->ptr++;
}

int
main(void)
{
    /* test with cat implementation */
    FILE *fp = fopen("exercise-8-2.c", "r");
    if (!fp) return -1;

    int c;
    while ((c = getc(fp)) != EOF)
        write(1, &c, 1);
    return 0;
}
