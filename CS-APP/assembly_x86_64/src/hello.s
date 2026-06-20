
# let's define what a location counter means
# location counter, or the dot '.' represents the current location in memory where the assembler
# 	is placing the next byte of data or instruction

.global _start
	
.section .rodata
msg:
	.ascii "Hello, world!\n"
len = . - msg 	# '.' means location counter, we subtract msg's address from current address

.section .text
_start:
	mov $1, %rax # syscall code for write
	mov $1, %rdi # file descriptor 1: stdout
	lea msg(%rip), %rsi # load effective address: load pointer to msg into %rsi for 2nd argument
	mov $len, %rdx # 3rd argument
	syscall
	
	mov $60, %rax # syscall exit
	xor %rdi, %rdi # xor %rdi 
	syscall	
