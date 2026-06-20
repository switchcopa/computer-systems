/* Exercise 8-4. The standard library function
 *      int fseek(FILE *fp, long offset, int origin)
 * is identical to lseek except that fp is a file pointer
 * instead of a file descriptor and return value is an int
 * status, not a position. Write fseek. Make sure that your
 * fseek coordinates properly with the buffering done for
 * the other functions of the library.
 */

#include "FILE.h"

int fseek(FILE *fp, long offset, int origin)
{
    if ((fp->flag & _ERR) || offset < 0)
        return -1;
    
    if (!(fp->flag & _UNBUF) && base != NULL)
    {
        if (fp->flag & _WRITE)
            flush(fp);
        else if (fp->flag & _READ)
        {
            fp->cnt = 0;
            fp->ptr = fp->base;
        }
    }

    return (lseek(fp->fd, offset, origin) >= 0) ? 0 : -1;
}
