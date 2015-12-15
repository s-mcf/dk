#include "arch/x86/video.h"
#include "arch/x86/keyboard.h"
#include "arch/x86/interrupt.h"

void kernel_main() {
	video_init();

	puts("Hello world!");

	init_idt();
	kb_init();

	__asm__ volatile ("sti");

	while(1);
}
