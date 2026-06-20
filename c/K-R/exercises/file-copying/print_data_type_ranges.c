#include <limits.h>
#include <stdio.h>

int main(void) {
    printf("The range of a signed char: %d -> %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("The range of a unsigned char: 0 -> %d\n\n", UCHAR_MAX);

    printf("The range of a signed short: %d -> %d\n", SHRT_MIN, SHRT_MAX);
    printf("The range of a unsigned short: 0 -> %d\n\n", USHRT_MAX);

    printf("The range of a signed int: %d -> %d\n", INT_MIN, INT_MAX);
    printf("The range of a unsigned int: 0 -> %u\n\n", UINT_MAX);

    printf("The range of a signed long: %ld -> %ld\n", LONG_MIN, LONG_MAX);
    printf("The range of a unsigned long: 0 -> %lu\n\n", ULONG_MAX);
    return 0;
}
