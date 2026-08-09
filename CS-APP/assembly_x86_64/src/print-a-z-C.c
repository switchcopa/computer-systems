
void _start(void)
{
    char arr[32];
    char *p = arr;
    long len = 28;
    char i;
    
    for (i = 'a'; i <= 'z'; i++) *p++ = i;
    *p++ = '\n';
    *p = 0;

    __asm__ __volatile__ (
            "movq   $1, %%rax\n\t"
            "movq   $1, %%rdi\n\t"
            "movq   %[arr], %%rsi\n\t"
            "movq   %[len], %%rdx\n\t"
            "syscall"
            :
            : [arr] "r" (arr),
              [len] "r" (len)
            : "%rax", "%rdi", "%rsi", "%rdx"
    );

    __asm__ __volatile__ (
            "movq   $60, %%rax\n\t"
            "movq   $0, %%rdi\n\t"
            "syscall"
            :
            :
            : "%rax", "%rdi"
    );
}
