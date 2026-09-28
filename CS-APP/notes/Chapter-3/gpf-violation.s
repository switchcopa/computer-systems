
/* compile with gcc -g gpf-violation.s -o test 
   and then run 'gdb ./test' then it will
   segfault at printf. Inspect the instruction
   pointer with x/i $rip, it will print:

(gdb) x/i $rip
=> 0x7ffff7c5b8e9 <printf+57>:  movaps %xmm0,-0x80(%rbp)

   You see that? It crashed right at the aligned
   move instruction, and the operating system
   said that it was a segmentation fault (SIGSEGV).
   If you're also on Linux, do:

   sudo dmesg | tail -n 5 

   Something like this will output:

    [270318.371407] traps: test[320025] general protection fault 
    ip:7ff79405b8e9 sp:7ffdaf57b9f8 
    error:0 in libc.so.6[5b8e9,7ff794024000+17b000]

   This shows exactly that a general 
   protection fault occurred.
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
