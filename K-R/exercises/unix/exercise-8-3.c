/* this is an implementation of the standard library function 
 * fopen(const char *filename, char *mode) using the UNIX/POSIX 
 * syscalls. more than that, we will solve exercise 8-3 from the 
 * K&R book, which goes like:
 * 8-3. Design and write _flushbuf, fflush and fclose.
 */

#include <syscalls.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define NULL        (void *)0
#define EOF         (-1)
#define OPEN_MAX    20

#define DEFAULT_PERMS 0666

typedef struct _iobuf
{
    int     cnt;    /* characters left */
    char    *ptr;   /* next character position */
    char    *base;  /* location of buffer */
    int     flag;   /* mode of file access */
    int     fd;     /* file descriptor */
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

enum _flags
{
    _READ   = 01,
    _WRITE  = 02,
    _UNBUF  = 04,
    _EOF    = 010,
    _ERR    = 020
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     (((p)->flag & _EOF) != 0)
#define ferror(p)   (((p)->flag & _ERR) != 0)
#define fileno(p)   ((p)->fd)

#define getc(p)     ((--(p)->cnt >= 0) \
                                   ? (unsigned char) *((p)->ptr++) : _fillbuf((p)))
#define putc(x, p)  ((--(p)->cnt >= 0) \
                                   ? (unsigned char) *((p)->ptr++) = (x) : _flushbuf((x), (p)))

// info is in the K&R book

#define getchar()   getc(stdin)
#define putcher(x)  putc((x), stdout)

FILE *mfopen(const char * restrict filename, 
        char * restrict mode);

int flush(FILE *stream);

int mfclose(FILE *stream);

/* mfopen: a simple implementation of the 
 * standard library function fopen()
 */
FILE *
mfopen(const char * restrict filename,
        char * restrict mode)
{
    FILE *p;
    int fd;
    for (p = _iob; p < _iob + OPEN_MAX; p++)
        if ((p->flag & (_READ | _WRITE)) == 0)
            break; // found empty slot
    if (p >= _iob + OPEN_MAX)
       return NULL; // no empty slot

    switch (*mode)
    {
        case 'r':
            fd = open(filename, O_RDONLY, 0);
            break;
        case 'w':
            fd = open(filename, O_CREAT | O_WRONLY, DEFAULT_PERMS);
            break;
        case 'a':
            fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, DEFAULT_PERMS);
            break;
        default:
            return NULL; // at this point. maybe get more edge cases later
    }

    if (fd == -1) return NULL;
    p->fd = fd;
    p->cnt = 0;
    p->base = p->ptr = NULL;
    p->flag = (*mode == 'r') ? _READ : _WRITE;
    return p;
}

/* _fillbuf: allocate and fill the 
 * input buffer
 */
int
_fillbuf(FILE *fp)
{
    int bufsize;

    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL)
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0)
    {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

/* _flushbuf: (the internal helper of putc) flush the full buffer into the output stream */
int
_flushbuf(int c, FILE *fp)
{
    unsigned nc;
    int bufsize;

    if (((fp->flag & (_WRITE | _ERR)) != _WRITE)
        || (fp->flag & _EOF) || fp->base == NULL)
    {
        fp->flag |= _ERR;
        return EOF;
    }

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    nc = fp->ptr - fp->base;
    if (write(fp->fd, fp->base, nc) != nc)
    {
        fp->flag |= _ERR;
        return EOF;
    }

    fp->ptr = fp->base;
    *(fp->ptr++) = (unsigned char) c;
    fp->cnt = bufsize - 1;
    return c;
}

/* flush: flush whatever buffer there is to the output FILE *stream */
int
flush(FILE *fp)
{
    int n;

    if ((fp->flag & (_WRITE | _ERR | _EOF)) != _WRITE)
        return EOF;

    if ((n = fp->ptr - fp->base) > 0)
        if (write(fp->fd, fp->base, n) != n)
        {
            fp->flag |= _ERR;
            return EOF;
        }

    fp->ptr = fp->base;
    fp->cnt = (fp->flag & _UNBUF) ? 0 : BUFSIZ;

    return 0;
}

/* mfclose: close the file by callling flush, free memory and make the slot in _iob
 * reusable again */
int
mfclose(FILE *fp)
{
    int rv;
    if (fp == NULL) return EOF;
    if (fp->flag & _WRITE)
        if (flush(fp) == -1)
            rv = EOF;
    if (!(fp->flag & _UNBUF) && fp->base != NULL)
    {
        free(fp->base);
        fp->base = NULL;
    }
    if (close(fp->fd) < 0)
        rv = EOF;

    fp->cnt = 0;
    fp->ptr = fp->base = NULL;
    fp->flag = 0;
    fp->fd = -1;

    free(fp);

    return rv;
}
