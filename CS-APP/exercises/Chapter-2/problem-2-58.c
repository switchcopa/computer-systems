
/*
Write a procedure is_little_endian that will return 1 when compiled and run
on a little-endian machine, and will return 0 when compiled and run on a big-
endian machine. This program should run on any machine, regardless of its word
size.
*/

/* is_little_endian: return 1 if the local machine is little endian
 * else return 0 */

#include <stdio.h>
#include <stdint.h>

int is_little_endian(void)
{
    int32_t  x = 0x12345678;
    uint8_t *p = (int8_t *)&x;

    return *p == 0x78;
}

void main(void)
{
    if (is_little_endian())
        printf("Little Endian\n");
    else
        printf("Big Endian\n");
}
