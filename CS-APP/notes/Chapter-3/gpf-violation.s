
/* Compile this with gcc -g gpf-violation.s -o test 
   and then run 'gdb ./test' then it will
   segfault at printf. Inspect the instruction
   pointer with x/i $rip, it will print:

(gdb) x/i $rip
=> 0x7ffff7c5b8e9 <printf+57>:  movaps %xmm0,-0x80(%rbp)

   You see that? It crashed right at the aligned
   move instruction, the CPU raises a GPF, and
   the operating system intercepts that exception,
   and said that it was a segmentation fault (SIGSEGV).
   If you're also on Linux, do:

   sudo dmesg | tail -n 5 

   Something like this will output:

    [270318.371407] traps: test[320025] general protection fault 
    ip:7ff79405b8e9 sp:7ffdaf57b9f8 
    error:0 in libc.so.6[5b8e9,7ff794024000+17b000]

   This shows exactly that a general 
   protection fault occurred.

   Now that we are 100% sure that a general protection fault
   was the purpose of the crash, we can analyze properly
   why that happened.

   The System V ABI AMD64 specifically mentions that right
   before a call instruction, the stack pointer should be
   16-byte aligned:

   "3.2.2 The Stack Frame
    The end of the input argument area shall be aligned on a 16
    (32 or 64, if __m256 or __m512 is passed on stack) byte boundary.
    In other words, the stack needs to be 16 (32 or 64) byte aligned
    immediately before the call instruction is executed."

   That said, compiler developers can write optimized library
   code that uses instructions that rely on that assumption,
   though it's more like a guarantee (e.g. vmovaps, vmovdqa, ...).
*/

    .global main
    .extern printf

    .data
fmt:
    .asciz "Value: %f\n"

    .text
main:
    pushq   %rbp
    movq    %rsp, %rbp
    pushq   %rbx // this breaks the alignment
    leaq    fmt(%rip), %rdi
    movsd   .LC0(%rip), %xmm0
    call    printf
    addq    $8, %rsp
    movq    $0, %rax
    popq    %rbx
    popq    %rbp
    ret

.section .rodata
.LC0:
    .quad 0x400921fb54442d18
