/*
2.72 ◆◆
You are given the task of writing a function that will copy an integer val into a
buffer buf, but it should do so only if enough space is available in the buffer.
Here is the code you write: */

/* Copy integer into buffer if space is available */
/* WARNING: The following code is buggy */

/*

void copy_int(int val, void *buf, int maxbytes) {
    if (maxbytes-sizeof(val) >= 0)
        memcpy(buf, (void *) &val, sizeof(val));
}

This code makes use of the library function memcpy. Although its use is a bit
artificial here, where we simply want to copy an int, it illustrates an approach
commonly used to copy larger data structures.
You carefully test the code and discover that it always copies the value to the
buffer, even when maxbytes is too small.
A. Explain why the conditional test in the code always succeeds. Hint: The
sizeof operator returns a value of type size_t.
B. Show how you can rewrite the conditional test to make it work properly.
*/

/*
A. According to C's integer signedness promotion rules, if we perform an arithmetic
operation between a signed integer and an unsigned integer, the signed operand is
implicitly casted into an unsigned integer. Here, sizeof(val) is of type size_t,
which is a typedef for an unsigned long on x86-64 Linux, and maxbytes is declared to
be a signed integer. The result of the operation is also an unsigned. Therefore, if
maxbytes = 3, and sizeof(int) = 4, then 3 - 4 = (size_t)-1 = SIZE_MAX >= 0, which is
always true when maxbytes < sizeof(int).

B. What I can do, is simply change the conditional test to:

    if (maxbytes >= sizeof(val))
        memcpy(buf, (void*)&val, sizeof(val));

That's it! For more compatibility and convention, we could change the type of maxbytes
to a size_t instead of int.

Fun fact: Run this program on your machine to see your machine's endianness!
If 12 is the first byte, your machine is big-endian. If it's 78 instead, your machine is
little-endian.
*/

#include <stdio.h>
#include <string.h>

void copy_int(int val, void *buf, size_t maxbytes)
{
    if (maxbytes >= sizeof(val))
        memcpy(buf, &val, sizeof(val));
}

int main(void)
{
    int val = 0x12345678;

    /* inspect buf in hexadecimal in a debugger */
    unsigned char buf[sizeof(int)];
    copy_int(val, buf, sizeof(buf));

    for (size_t i = 0; i < sizeof(int); i++)
        printf("%X ", buf[i]);
    printf("\n");
    return 0;
}
