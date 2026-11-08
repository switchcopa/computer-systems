
#include "svm.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

constexpr uint64_t SECTION_DATA = 0x1000;
uint8_t *open_bin(const char *fn, long *size);

int main(void)
{
    struct cpu_t *cpu = calloc(1, sizeof(struct cpu_t));
    if (!cpu)
        return -1;

    cpu->regs[REG_RSP] = RSP_INIT;
    cpu->rip = RIP_INIT;

    long size;
    uint8_t *bin = open_bin("output.bin", &size);
    if (!bin)
        return -1;

    memcpy(cpu->dmem, bin, size);
    enum status stat = run_cpu(cpu);

    return stat;
}

uint8_t *open_bin(const char *fn, long *out_size)
{
    long size;
    uint8_t *buf;
    FILE *bin = fopen(fn, "rb");
    if (!bin) {
        fprintf(stderr, "failed to open file\n");
        return nullptr;
    }

    fseek(bin, 0, SEEK_END);
    size = ftell(bin);
    fseek(bin, 0, SEEK_SET);

    buf = malloc(size);
    fread(buf, 1, size, bin);
    fclose(bin);

    *out_size = size;
    return buf;
}
