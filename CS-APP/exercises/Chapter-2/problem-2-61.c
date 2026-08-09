
/*

Write C expressions that evaluate to 1 when the following conditions are true and
to 0 when they are false. Assume x is of type int.
A. Any bit of x equals 1.
B. Any bit of x equals 0.
C. Any bit in the least significant byte of x equals 1.

D. Any bit in the most significant byte of x equals 0.

Your code should follow the bit-level integer coding rules (page 164), with the
additional restriction that you may not use equality (==) or inequality (!=) tests.

*/

#define ALL_ONES(x) (!(~(x)))
#define ALL_ZEROES(x) (!(x))
#define ALL_LSB_ARE_ONES(x) (!(0xFF ^ ((x) & 0xFF)))
#define ALL_MSB_ARE_ZEROES(x) \
            (!(((x) >> ((sizeof(int) - 1) << 3)) & 0xFF))
