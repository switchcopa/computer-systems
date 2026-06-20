#include <stdio.h>
#include <stdint.h>

/* Write a function setbits(x, p, n, y) that returns x with the n bits 
that begin at p set to the rightmost n bits of y, leaving the other bits unchanged */

void setbits(int *x, int p, int n, int y);

/* Write a function that swaps the 4 upper bits and lower 4 bits (nibbles) of an 8-bit unsigned integer */

void swap_nibbles(uint8_t *x);

/* Write a function that counts the number of 1s in an unsigned 32-bit integer */

int count_ones(uint32_t x);
int kr_countsetbits(uint32_t x);

/* Write a function that reverses the bits of an 32-bit unsigned integer */

uint32_t reverse_bits(uint32_t x);

/* Write a function that takes a 32-bit unsigned integer and returns 1 if there's exactly one set bit, 0 otherwise */

int one_bit_set(uint32_t x);

/* Write a function that swaps Endianness for a 32-bit unsigned integer */

void swap_endian(uint32_t *x);
void swap(uint8_t *a, uint8_t *b); // support

/* Given: You are in a little-endian machine. */

uint8_t buf[8] = {
	0x00, 0x11, 0x22, 0x33,
	0x44, 0x55, 0x66, 0x77
};

/* You do: */

uint32_t *pb = (uint32_t *) buf;

/* What is the hex value of pb[0]? pb[1]? and what happens to the hex value of p[0] when you reverse its endian */ 

/* Answer: pb = (uint32_t *) buf becomes a pointer to a uint32_t, which is 0x33221100, since the MSB in pb[0] is 0x33, and we're in a little-endian
	machine and the uint8_t's get packed to 4 bytes for each.
	Therefore pb[0] = 0x33221100
	and pb[1] = 0x77665544.
	swap_endian(&pb[0]) -> pb[0] = 0x00112233.
	We test this in line 72.
*/	

/* Task: Take 4 bytes from a message uint8_t msg[4], pack them to a uint32_t word, and interpret them as big-endian. 
	Answer is in line 80.
*/

/* Write another swap_endian function that swaps endianness of a uint32_t using uint8_t bytes and OR bit manipulation */

void better_swap_endian(uint8_t *bfp);

int main(void) {
        int x = 0b10101111, y = 0b00001100;
        setbits(&x, 4, 3, y);
        printf("%d\n", x);

	uint8_t z = 0b10100011;
	swap_nibbles(&z);
	printf("%d\n", z == 0b00111010);
	
	uint32_t t = 314551;
	printf("%d\n", kr_countsetbits(t)); // should be 11
	
	uint32_t p = 1;
        p = reverse_bits(p);
        printf("%u, %u\n", p, ~0U);
	
	uint32_t n = 0x12345678;
	swap_endian(&n);
	printf("%d\n", n == 0x78563412);
	
	printf("pb[0] = 0x%X, pb[1] = 0x%X\n", pb[0], pb[1]);
	swap_endian(&pb[0]);
	printf("pb[0] = 0x%X\n", pb[0]);

	uint8_t msg[4] = {0x00, 0x11, 0x67, 0x77};
	uint32_t *ptr = (uint32_t *) msg; // now ptr holds 0x77671100, for big-endian -> 0x00116777
	printf("packed msg: 0x%X\n", *ptr);
	swap_endian(ptr);
	printf("swapped for big-endian: 0x%X\n", *ptr);
	
	uint8_t bfp[4] = {0x12, 0x34, 0x56, 0x78};
	uint32_t *endian = (uint32_t *) bfp;
	better_swap_endian(bfp);
	printf("swapped for big-endian: 0x%X\n", *endian); // 0x78563412

	return 0;
}

void setbits(int *x, int p, int n, int y) { 
	 *x = (~(((1 << n) - 1) << (p - n + 1)) & *x) | ((((1 << n) - 1) & y) << (p - n + 1)) ;
}

void swap_nibbles(uint8_t *x) {
	uint8_t mask = (1 << 4) - 1;
	*x = ((mask & *x) << 4) | (((mask << 4) & *x) >> 4);
}

int count_ones(uint32_t x) {
        int c = 0;
        for (int k = 0; k < 32; k++)
                if (x & (1 << k))
                        c++;

        return c;
}

int kr_countsetbits(uint32_t x) {
	int c = 0;
	while (x) {
		x &= (x - 1);
		c++;
	}

	return c;	
}

uint32_t reverse_bits(uint32_t x) {
	uint32_t result = 0;
	for (int i = 0; i < 32; i++) {
		result <<= 1;
		result |= (x & 1);
		x >>= 1;
	}

	return result;
}

int one_bit_set(uint32_t x) {
	return x != 0 && (x & (x - 1)) == 0;
}

void swap_endian(uint32_t *x) {
	uint8_t *p = (uint8_t *) x;
	swap(&p[0], &p[3]);
	swap(&p[1], &p[2]);
}

void swap(uint8_t *a, uint8_t *b) {
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void better_swap_endian(uint8_t *ptr) {
	(ptr[0] << 24)  | (ptr[1] << 16) |
		(ptr[2] >> 16) | (ptr[3] >> 24);
}
