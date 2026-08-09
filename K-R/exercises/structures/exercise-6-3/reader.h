#ifndef READER_H
#define READER_H

#define INPUT_BUFFER_SIZE 5024

#include <sys/types.h>

struct input_reader
{
    char buffer[INPUT_BUFFER_SIZE];
    ssize_t buflen;
    int bufp;
};

ssize_t read_input(struct input_reader *r);

#endif
