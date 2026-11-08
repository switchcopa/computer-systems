
# test.s
.pos 0x0
init:
    irmovq $100, %rax
    irmovq $200, %rbx
    addq %rax, %rbx
    rmmovq %rbx, 8(%rsp)
    mrmovq 8(%rsp), %rcx
    call target
    halt

.pos 0x100
target:
    subq %rcx, %rax
    pushq %rax
    popq %rdx
    ret
