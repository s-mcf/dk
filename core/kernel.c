#include "arch/x86/video.h"
#include "arch/x86/keyboard.h"
#include "arch/x86/interrupt.h"
#include "arch/x86/gdt.h"

void kernel_main() {
	gdt_install();
	video_init();

	puts("-- DK: Donkey Kernel --\n");

	init_idt();
	kb_init();
	puts("Interrupts ready!\n");

	__asm__ volatile ("sti");

	puts("Thus begins the infinite loop\n");
	while(1);
}
