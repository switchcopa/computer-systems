  
/* 
   *     Intro:
   *     SHA-2 (Secure Hash Algorithm 2) is a set of cryptographic hash functions designed by the United States National Security Agency (NSA)
   *     and first published in 2001. They are built using the Merkle–Damgård construction, from a one-way compression function itself 
   *     built using the Davies–Meyer structure from a specialized block cipher. 
*/

/*
  * Take a message of arbitrary length (array of bytes)
  *
  * Append a single 1 bit, followed by enough 0 bits so that the total length (in bits) ≡ 448 mod 512
  * This ensures the padded message length is 64 bits short of a multiple of 512 bits
  *
  * Append the 64-bit big-endian length of the original message
  * This stores the original message length in bits at the end of the last 512-bit block
  *
  * Take each 512-bit block (64 bytes) of padded_msg
  *
  * Break it into 16 words of 32 bits each (uint32_t W[16])
  * Each word is big-endian: most significant byte first
  *
  * SHA-256 uses 64 words per block (W[0..63])
  *
  * The first 16 words = packed words from the block (W[0..15])
  *
  * Remaining words (W[16..63]) are computed with:
  *    W[i] = σ1(W[i-2]) + W[i-7] + σ0(W[i-15]) + W[i-16]
  *    σ0(x) = ROTR7(x) ^ ROTR18(x) ^ (x >> 3)
  *    σ1(x) = ROTR17(x) ^ ROTR19(x) ^ (x >> 10)
  *
  * Initialize working variables a..h with current hash values H[0..7]
  *
  * For i = 0 to 63 (64 rounds):
  *    T1 = h + Σ1(e) + Ch(e,f,g) + K[i] + W[i]
  *    T2 = Σ0(a) + Maj(a,b,c)
  *    Update working variables:
  *      h = g
  *      g = f
  *      f = e
  *      e = d + T1
  *      d = c
  *      c = b
  *      b = a
  *      a = T1 + T2
  *    Where:
  *      Ch(x,y,z) = (x & y) ^ (~x & z)
  *      Maj(x,y,z) = (x & y) ^ (x & z) ^ (y & z)
  *      Σ0(x) = ROTR2(x) ^ ROTR13(x) ^ ROTR22(x)
  *      Σ1(x) = ROTR6(x) ^ ROTR11(x) ^ ROTR25(x)
  *      ROTRn(x) = rotate x right by n bits
  *      K[i] = round constant (first 32 bits of cube roots of first 64 primes)
  *
  * After processing the block:
  *    Add working variables a..h back into H[0..7] (mod 2^32)
  *
  * After all blocks are processed:
  *    Concatenate H[0..7] to produce the final 256-bit hash
*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define MSG_LENGTH 12

uint8_t msg[MSG_LENGTH] = "my password";

/*
uint8_t msg[MSG_LENGTH] = {
    0x2E, 0xF7, 0x9C, 0x41, 0xB3, 0x08, 0xCD, 0x6A,
    0x5F, 0xE2, 0x1D, 0x84, 0x77, 0xA9, 0x33, 0xCE,
    0x90, 0x4B, 0xDC, 0x25, 0x7A, 0xB6, 0x01, 0xE8,
    0x59, 0xC4, 0x3F, 0x92, 0x68, 0xD5, 0x0B, 0x74,
    0xAF, 0x26, 0x99, 0x52, 0xBD, 0x10, 0xE3, 0x7C,
    0x47, 0x8A, 0x15, 0xF0, 0x2A, 0x66, 0xC9, 0xB1
};
*/

uint32_t H[8] = {
    0x6a09e667,
    0xbb67ae85,
    0x3c6ef372,
    0xa54ff53a,
    0x510e527f,
    0x9b05688c,
    0x1f83d9ab,
    0x5be0cd19
};


static const uint32_t K[64] = {
  0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
  0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
  0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
  0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
  0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
  0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
  0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
  0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
  0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
  0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
  0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
  0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
  0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
  0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
  0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
  0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

#define ROTR(x,n) (((x) >> (n)) | ((x) << (32-(n))))
#define Ch(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define Maj(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SIG0(x) (ROTR(x,2) ^ ROTR(x,13) ^ ROTR(x,22))
#define SIG1(x) (ROTR(x,6) ^ ROTR(x,11) ^ ROTR(x,25))


int main(void) {
        uint64_t msg_bitlen = MSG_LENGTH * 8;
        uint64_t padded_len = ((MSG_LENGTH + 9 + 63) / 64) * 64;
        uint8_t *padded_msg = malloc(padded_len);

        for (uint64_t i = 0; i < padded_len; i++)
                padded_msg[i] = 0U;

        memcpy(padded_msg, msg, MSG_LENGTH);
        padded_msg[MSG_LENGTH] = 0x80;

        for (int i = 0; i < 8; i++)
                padded_msg[padded_len - 1 - i] = (msg_bitlen >> (8 * i)) & 0xFF;

        for (uint64_t block = 0; block < padded_len; block += 64) {
                uint32_t W[64];
                for (int t = 0; t < 16; t++) {
                        W[t] = ((uint32_t)padded_msg[block + 4*t] << 24) |
                               ((uint32_t)padded_msg[block + 4*t + 1] << 16) |
                               ((uint32_t)padded_msg[block + 4*t + 2] << 8) |
                               ((uint32_t)padded_msg[block + 4*t + 3]);
                }
                for (int t = 16; t < 64; t++) {
                        W[t] = SIG1(W[t-2]) + W[t-7] + SIG0(W[t-15]) + W[t-16];
                }

                uint32_t a = H[0];
                uint32_t b = H[1];
                uint32_t c = H[2];
                uint32_t d = H[3];
                uint32_t e = H[4];
                uint32_t f = H[5];
                uint32_t g = H[6];
                uint32_t h = H[7];

                for (int t = 0; t < 64; t++) {
                        uint32_t T1 = h + SIG1(e) + Ch(e,f,g) + K[t] + W[t];
                        uint32_t T2 = SIG0(a) + Maj(a,b,c);

                        h = g;
                        g = f;
                        f = e;
                        e = d + T1;
                        d = c;
                        c = b;
                        b = a;
                        a = T1 + T2;
                }

                H[0] += a;
                H[1] += b;
                H[2] += c;
                H[3] += d;
                H[4] += e;
                H[5] += f;
                H[6] += g;
                H[7] += h;
        }
  
        uint8_t hash[32];
        for (int i = 0; i < 8; i++) {
                hash[4*i]     = (H[i] >> 24) & 0xFF;
                hash[4*i + 1] = (H[i] >> 16) & 0xFF;
                hash[4*i + 2] = (H[i] >> 8)  & 0xFF;
                hash[4*i + 3] = H[i] & 0xFF;
        }

        for (int i = 0; i < 32; i++)
                printf("%02x", hash[i]);
        printf("\n");

        free(padded_msg);
        return 0;
}
