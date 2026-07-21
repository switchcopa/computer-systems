
/*
You are given the task of patching the vulnerability in the XDR
code shown in the aside on page 136 for the case where both data
types int and size_t are 32 bits. You decide to eliminate the
possibility of the multiplication overflowing by computing the
number of bytes to allocate using data type uint64_t. You replace
the original call to malloc as follows:

uint64_t asize = ele_cnt * (uint64_t) ele_size;
void *result = malloc(asize);

recall that the argument to malloc has type size_t.

A. Does your code provide any improvement over the original?
B. How would you change the code to eliminate the vulnerability?
*/

/*
A. Well, I think the code provides some improvement, although
the vulnerability for integer overflow is still possible.
The main improvement comes with the maximum range that a size_t
integer can represent, depending on the architecture. On a 32-bit
system, a size_t is only 32 bits, and there is more risk to
overflow than an 64-bit unsigned integer. To write code that is
independent of the architecture's native pointer width, the
solution to compute asize as a uint64_t is perfect.
For the ele_cnt case, it is declared to be an int in copy_elements'
arguments, which is a signed integer. What if ele_cnt is negative?
The problem of the overflow vulnerability arises, because once
we compute

uint64_t asize = ele_cnt * (uint64_t) ele_size;

ele_cnt is implicitly casted to a uint64_t, which can lead to
a disaster in this case.

Example:
If ele_cnt = -1, then (uint64_t)ele_cnt = UINT64_MAX - 1,
and the computation ele_cnt * (uint64_t) ele_size overflows
in this unsigned multiplication operation.

Another problem is how the library function malloc is declared.
It takes a size argument of type size_t, which on a 32-bit system
for example, is only 32 bits wide. That said, when we call
malloc(asize), the upper 32 bits of asize are truncated,
which keeps the same bug with no change.

B. To eliminate the vulnerability, I would either:

1. Declare ele_size to be a size_t, and then explicitly
cast them to uint64_t s when we want to compute the size for
malloc, and then check for overflow by comparing the total
size, with the macros that represent the range of the size
we want to compare, provided in <limits.h> or <stdint.h>.
OR:
2. Initially return NULL if ele_cnt fails to satisfy being
positive, and use division to see whether overflow is possible.

Side note: Also, I noticed that the code performs pointer
arithmetic on void pointers, which is a compile-time error;
this can be solved by casting the target to a char * or a 
uint8_t * for precision.
*/

#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

void *copy_elements(void *src[], int ele_cnt, size_t ele_size)
{
    if (ele_cnt <= 0 ||
        ele_size > SIZE_MAX / ele_cnt)
        return NULL;

    void *result = malloc(ele_cnt * ele_size);
    if (result == NULL) return NULL;

    char *next = (char*)result;
    int i;
    for (i = 0; i < ele_cnt; i++)
    {
        memcpy(next, src[i], ele_size);
        next += ele_size;
    }

    return result;
}
