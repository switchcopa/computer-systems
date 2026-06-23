
/* This is a test to see how much depth is allowed for
 * each Linux x86-64 stack, in the virtual address space
 * of a process */

/* we should compile this with -O0 as in zero optimizations
 * by the compiler */

#include <stdio.h>

static long  b = 0;
static void* last_addr = NULL;

void blow_stack(void)
{
    int var = 0; // this forces a spot on the current stack frame
    void *curr_addr = (void*)&var;

    if (last_addr)
    {
        // this is because the stack grows down, and the top of the stack
        // is at a lower address
        long bytes = (long)last_addr - (long)curr_addr;
        b += bytes;
        static long count = 0;
        count++;
        if (count % 10000 == 0)
            printf("Call #%ld | Frame Size: %ld bytes | Total Stack Used: %ld bytes\n",
                    count, bytes, b);
    }

    last_addr = curr_addr;
    blow_stack();
}

int main(void)
{
    blow_stack();
}
