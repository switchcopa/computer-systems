
/* 
 *
Imagine a remote device sends you a single 32-bit unsigned integer (uint32_t) over the network. Because it comes from the network, it is strictly Big-Endian.

This 32-bit packet contains three distinct fields packed tightly together:

    Status Code: The most significant 4 bits (Bits 28–31).

    Temperature: The middle 16 bits (Bits 12–27).

    Device ID: The least significant 12 bits (Bits 0–11).

Your Task

    Write a C program that takes a hardcoded hexadecimal raw value, manually rearranges
    the bytes to match your local machine's endianness using bitwise operators, and then
    extracts the three hidden values using bit masks and shifts.
    
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PACKET_BUF_SIZE     16
#define STR_HEX_32_BIT_SIZE 8

static inline int endianness(void)
{
    uint32_t u = 0x12345678;
    uint8_t *p = (uint8_t *)&u;

    if (p[0] == 0x12)
        return 0; // big endian
    else
        return 1; // little endian
}

static uint32_t htou32(const char *str)
{
    uint32_t result = 0U;
    int bound = STR_HEX_32_BIT_SIZE;
    int i = 0;
    char c;

    if (str[0] == '0' &&
       (str[1] == 'x' || str[1] == 'X'))
    {
        i = 2;
        bound += 2;
    }

    for (; i < bound && (c = str[i]); i++)
    {
        uint32_t val = 0;
        if (c >= '0' && c <= '9')
            val = c - '0';
        else if (c >= 'A' && c <= 'F')
            val = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f')
            val = c - 'a' + 10;
        else
            break;
        result = (result << 4) | val;
    }

    return result;
}

static inline uint32_t to_big_endian(uint32_t u)
{
    return ((u << 24) & 0xFF000000) |
           ((u <<  8) & 0x00FF0000) |
           ((u >>  8) & 0x0000FF00) |
           ((u >> 24) & 0x000000FF);
}

int main(void)
{
    char packet_buf[PACKET_BUF_SIZE];
    char *success = fgets(packet_buf, PACKET_BUF_SIZE, stdin);
    if (!success)
    {
        fprintf(stderr, "failed to get input packet\n");
        exit(EXIT_FAILURE);
    }

    uint32_t packet = htou32(packet_buf);

    if (endianness() == 1)
        packet = to_big_endian(packet);
    uint8_t status  = ~0U & (packet >> 28);
    uint16_t temp   = (~0U >> 16) & (packet >> 12);
    uint16_t dev_id = (~0U >> 20) & packet;

    printf("Status Code:  0x%X\n", status);
    printf("Temperature:  0x%X\n", temp);
    printf("Device ID:    0x%X\n", dev_id);
    return 0;
}
