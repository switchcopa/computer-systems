#include "reader.h"
#include <stdio.h>
#include <sys/types.h>

ssize_t read_input(struct input_reader *r)
{
    r->bufp = 0;
    int c;

    while ((c = getchar()) != EOF && r->bufp < INPUT_BUFFER_SIZE - 1)
        r->buffer[r->bufp++] = (unsigned char)c;

    if (c == EOF && r->bufp == 0)
        return -1;

    r->buffer[r->bufp] = '\0';
    r->buflen = r->bufp;
    r->bufp = 0;
    return r->buflen;
}
