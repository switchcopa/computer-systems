
/*
2.71 ◆
You just started working for a company that is implementing a set of procedures
to operate on a data structure where 4 signed bytes are packed into a 32-bit
unsigned. Bytes within the word are numbered from 0 (least significant) to 3
(most significant). You have been assigned the task of implementing a function
for a machine using two’s-complement arithmetic and arithmetic right shifts with
the following prototype:

Declaration of data type where 4 bytes are packed
into an unsigned

typedef unsigned packed_t;

Extract byte from word. Return as signed integer

int xbyte(packed_t word, int bytenum);

That is, the function will extract the designated byte and sign extend it to be
a 32-bit int.

Your predecessor (who was fired for incompetence) wrote the following code:

Failed attempt at xbyte
int xbyte(packed_t word, int bytenum)
{
    return (word >> (bytenum << 3)) & 0xFF;
}

A. What is wrong with this code?
B. Give a correct implementation of the function that uses only left and right
shifts, along with one subtraction.
*/

/*
A. The problem is that the right shifts (word >> (bytenum << 3)) are performed
using logical shifts, on the 32-bit unsigned type, and that sizeof(int) = 4.
Let's take a look at an example:

Assume word = 0x00FF0000, and we want to get the second byte.
The first computation 2 << 3 = 16 is okay.
Then 0x00FF0000 >> 16 = 0x000000FF. Now interpreting this as an integer type,
the decimal result is 255. What we expected was -1, this is not looking good.

We have two choices:

1. We exploit the machine's fundamental parameter for two's complement
arithmetic support, and extend the sign bit from the most significant bit,
which is the 31st bit, all the way to the least significant bit of the first
byte, which would actually represent the signed integer we wanted, and potentially
become negative. Like:

shift = 
0x00FF0000 << shift = (int)0xFF000000 >> 24

0 = 24
1 = 16
2 = 8
3 = 0

(3 - bytenum) * 8

2. Or, use the 8-bit signed integer type provided by stdint.h (C99 and above),
which is int8_t, and then change the function prototype to return a int8_t instead.
Because of C's integer promotion rules, doing something like:

int x = xbyte(0x00FF0000, 2);

will result to x = -1.
The latter is simpler, but we are going to implement the first one anyways.

B.
*/

int xbyte(unsigned word, int bytenum)
{
    int shift = (3 - bytenum) << 3;
    int x = word << shift;
    return x >> 24;
}

#include <stdio.h>
#include <stdint.h>

void main(void)
{
    int x = xbyte(0x00B50000, 2);
    printf("0x%X = %d\n", x, x);
}
