

/* let's say for simplicity that we support only capital letters
 * in the hexadecimal representation, and all hex strings start with
 * "0x" */
#include <stdio.h>
#include <string.h>

void utoh(char *hex, unsigned x); 
unsigned htou(char *hex);
void strrev(char *str);

static char table_decimal_to_hex[] = 
{ '0', '1', '2', '3', 
  '4', '5', '6', '7',
  '8', '9', 'A', 'B',
  'C', 'D', 'E', 'F'
};

int main(void)
{
    char hex[32];
    utoh(hex, 314156);
    strrev(hex+2);
    printf("%s\n", hex);

    printf("%u\n", htou("0xC0DE"));
    return 0;
}

void utoh(char *hex, unsigned x)
{
    hex[0] = '0';
    hex[1] = 'x';

    unsigned q = x;
    unsigned r;
    int i = 2;

    while (q)
    {
        r = q % 16;
        q /= 16;
        hex[i++] = table_decimal_to_hex[r];
    }
    hex[i] = '\0';
}

unsigned htou(char *hex)
{
    unsigned result = 0;
    int i = 2;
    char c;

    while ((c = hex[i]))
    {
        unsigned val = 0;
        if (c >= '0' && c <= '9')
            val = c - '0';
        else if (c >= 'A' && c <= 'F')
            val = c - 'A' + 10;
        else break;
        result = (result << 4) | val;
        i++;
    }

    return result;
}

void strrev(char *str)
{
    int len = strlen(str);
    char temp;
    for (int i = 0; i < len / 2; i++)
    {
        temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}
