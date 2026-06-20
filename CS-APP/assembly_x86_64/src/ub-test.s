/* 
Translate the following C code to assembly:
void foo(int **q) {
        q = NULL;
}

int main(void) {
        int x = 42;
        int *p = &x;

        foo(&q);
        int arr[10];
        for (int i = 0; i < 10; i++)
                arr[i] = i; 
	printf("Hello World!\n");
        return 0;
}
*/

.section .rodata
hello: 
	.ascii "Hello, world!\n"
len = . - hello

.section .text
foo:
	movq $0, %rdi
	ret

_start:
	subq $16, %rsp
	movq $42, 8(%rsp)
	leaq 8(%rsp), %rax
	movq %rax, (%rsp)
	leaq (%rsp), %rdi
	call foo

	mov $1, %rax
	mov $1, %rdi
	lea hello(%rip), %rsi
	mov $len, %rdx
	syscall

	mov $60, %rax
	xor %rdi, %rdi
	syscall
