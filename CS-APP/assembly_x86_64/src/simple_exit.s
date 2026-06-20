
.global _start
_start:
	mov $60, %rax # syscall number for exit
	mov $42, %rdi # exit code
	syscall       # call kernel
