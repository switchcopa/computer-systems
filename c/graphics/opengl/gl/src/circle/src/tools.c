#include <stdio.h>
#include <sys/types.h>
#include "tools.h"

ssize_t read_file(char *buffer, const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
        return -1;

    fseek(fp, 0, SEEK_END);
    size_t s = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    ssize_t bytes = fread(buffer, sizeof(char), s, fp);
    if (bytes > 0 && bytes < BUFFER_SIZE - 1)
        buffer[bytes++] = '\0';

    fclose(fp);
    return bytes;
}
