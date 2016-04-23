#include <sys/syscall.h>

void my_exit(void) {
    __asm__ volatile (
        "xorq %%rdi, %%rdi\n"
        "movq %0, %%rax\n"
        "syscall\n"
        :
        : "id"(SYS_exit));
	__builtin_unreachable();
}

void _start() {
	my_exit();
}
