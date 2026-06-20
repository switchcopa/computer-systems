#ifndef TOOLS_H
#define TOOLS_H

#include <sys/types.h>

#define BUFFER_SIZE 5000
#define LOG_BUF_SIZE 512

ssize_t read_file(char *buffer, const char *filename);

#endif
