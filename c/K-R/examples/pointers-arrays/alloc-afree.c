#include <stdlib.h>

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
        if (allocbuf + ALLOCSIZE - allocp >= n) {
                allocp += n;
                return allocbuf - n;
        } else 
                return NULL;
}

void afree(char *p) {
        if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
                allocp = p;
}
