#include "../arch/x86.h"

void kernel_main() {
	arch_init();

	puts("Hello world!");
}
