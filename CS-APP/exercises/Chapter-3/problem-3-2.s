/*
Practice Problem 3.2 (solution page 361)
For each of the following lines of assembly language, determine the appropriate
instruction suffix based on the operands. (For example, mov can be rewritten as
movb, movw, movl, or movq.)*/

    movl    %eax, (%rsp)
    movw    (%rax), %dx
    movb    $0xFF, %bl
    movb    (%rsp,%rdx,4), %dl
    movq    (%rdx), %rax
    movw    %dx, (%rax)
