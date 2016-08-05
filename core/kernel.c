#ifdef __arm__

#include "../arch/arm/uart.h"

#elif __i386__

#include "arch/x86/video.h"
#include "arch/x86/keyboard.h"
#include "arch/x86/interrupt.h"
#include "arch/x86/gdt.h"

#endif


void echo(void) {
    while (1) {
        uart_putc(uart_getc());
    }
}

void kernel_main(void) {
#ifdef __arm__
    uart_init();
#elif __i386__
    gdt_install();
    video_init();
#endif
    puts("-- DK: Donkey Kernel --\n");

#ifdef __arm__
    echo();
#elif __i386__
    init_idt();
    kb_init();
    puts("Interrupts ready!\n");
    puts("Thus begins the infinite loop\n");
    while (1);
#endif
}
