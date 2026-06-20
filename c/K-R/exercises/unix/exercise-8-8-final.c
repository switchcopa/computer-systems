#include <stddef.h>


/* assuming we already included the header file
 * that has the Header union, etc... */
extern Header *freep;

unsigned bfree(char *p, unsigned n)
{
    Header *hp;
    long remaining_bytes;
    unsigned nunits;

    hp = (Header *)((p + sizeof(Header) - 1)/ sizeof(Header) * sizeof(Header));
    remaining_bytes = n - ((char*)hp - p);
    nunits = remaining_bytes/sizeof(Header);

    hp->s.size = nunits;

    if (freep == NULL)
    {
        extern Header base;
        base.s.ptr = freep = &base;
        base.s.size = 0;
    }

    free((void*)(hp+1));
    return hp->s.size;
 }
