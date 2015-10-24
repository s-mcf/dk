#include "../arch/x86.h"

char *vidmem;

void arch_init() {
	vidmem = (char*) _X86_VIDMEM;
}

void screen_clear() {
	char *vidptr = vidmem;
	for (int i = 0; i < _X86_SCREEN_COLS * _X86_SCREEN_ROWS * 2; i+=2) { // two-byte stride
		vidptr[i] = ' ';
		vidptr[i + 1] =	COLOR_LIGHT_GREY | COLOR_BLACK << 4;
	}
}

void puts(const char *s) {
	puts_color(s, COLOR_LIGHT_GREY, COLOR_BLACK);
}

void puts_color(const char *s, x86_colors fg, x86_colors bg) {
	char *vidptr = vidmem;
	unsigned int i = 0;
	for (char* t = (char*) s; *t; t++) {
		vidptr[i] = *t;
		vidptr[i + 1] = fg | bg << 4;
		i += 2;
	}
}
