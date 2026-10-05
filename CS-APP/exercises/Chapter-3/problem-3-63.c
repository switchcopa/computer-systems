
/*
3.63 ◆◆
This problem will give you a chance to reverse engineer a switch statement from
disassembled machine code. In the following procedure, the body of the switch
statement has been omitted:
p1 in %rdi, p2 in %rsi, action in %edx

.L8: MODE_E
    movl    $27, %eax
    ret

.L3: MODE_A
    movq    (%rsi), %rax
    movq    (%rdi), %rdx
    movq    %rdx, (%rsi)
    ret

.L5: MODE_B
    movq    (%rdi), %rax
    addq    (%rsi), %rax
    movq    %rax, (%rdi)
    ret

.L6: MODE_C
    movq    $59, (%rdi)
    movq    (%rsi), %rax
    ret

.L7: MODE_D
    movq    (%rsi), %rax
    movq    %rax, (%rdi)
    movl    $27, %eax
    ret

.L9: default
    movl    $12, %eax
    ret

(gdb) x/6gx 0x4006f8
0x4006f8: 0x00000000004005a1
          0x00000000004005c3
0x400708: 0x00000000004005a1
          0x00000000004005aa
0x400718: 0x00000000004005b2
          0x00000000004005bf

long switch_prob(long x, long n)
x in %rdi, n in %rsi

1  0000000000400590 <switch_prob>:
2  400590: 48 83 ee 3c             sub    $60,%rsi
3  400594: 48 83 fe 05             cmp    $5,%rsi
4  400598: 77 29                   ja     4005c3 <switch_prob+0x33>
5  40059a: ff 24 f5 f8 06 40 00    jmpq   *0x4006f8(,%rsi,8)

6  4005a1: 48 8d 04 fd 00 00 00 00 lea    0x0(,%rdi,8),%rax
8  4005a9: c3                      retq

9  4005aa: 48 89 f8                mov    %rdi,%rax
10 4005ad: 48 c1 f8 03             sar    $0x3,%rax
11 4005b1: c3                      retq

12 4005b2: 48 89 f8                mov    %rdi,%rax
13 4005b5: 48 c1 e0 04             shl    $0x4,%rax
14 4005b9: 48 29 f8                sub    %rdi,%rax
15 4005bc: 48 89 c7                mov    %rax,%rdi
16 4005bf: 48 0f af ff             imul   %rdi,%rdi

### switch_prob+0x33
17 4005c3: 48 8d 47 4b             lea    0x4b(%rdi),%rax 
18 4005c7: c3                      retq   

Figure 3.53 Disassembled code for Problem 3.63.
*/

long switch_prob(long x, long n) {
    long result = x;

    switch (n) {
    case 60:
    case 62:
        return x * 8;
    case 63:
        return x / 8;
    case 64:
        result = x * 15;
        x = result;
    case 65:
        x *= x;
    default:
        return x + 75;
    }

    return result;
}
