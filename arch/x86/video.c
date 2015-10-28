#include "arch/x86/video.h"

char *vidmem;
unsigned char pos = 0;

void video_init() {
	vidmem = (char*) _X86_VIDMEM;
}

void screen_clear() {
	char *vidptr = vidmem;
	for (int i = 0; i < _X86_SCREEN_COLS * _X86_SCREEN_ROWS * 2; i+=2) { // two-byte stride
		vidptr[i] = ' ';
		vidptr[i + 1] =	COLOR_LIGHT_GREY | COLOR_BLACK << 4;
	}
	pos = 0;
}

void putchar(char c) {
	putchar_color(c, COLOR_LIGHT_GREY, COLOR_BLACK);
}

void putchar_color(char c, x86_colors fg, x86_colors bg) {
	char *vidptr = vidmem;
	vidptr[pos] = c;
	vidptr[pos + 1] = fg | bg << 4;
	pos += 2;
}

void puts(const char *s) {
	puts_color(s, COLOR_LIGHT_GREY, COLOR_BLACK);
}

void puts_color(const char *s, x86_colors fg, x86_colors bg) {
	for (char* t = (char*) s; *t; t++) {
		// When we encounter a newline, wrap
		if (*t == '\n') {
			unsigned int cursor_row = i % 80;
			i += 80 - cursor_row;
			// If our index overflows the screen buffer, clear the screen and
			// start again from 0.
			if (i > 80 * 25) {
				screen_clear();
				i = 0;
			}
		} else {
			putchar(*t);
        }
		vidptr[i] = *t;
		vidptr[i + 1] = fg | bg << 4;
		i += 2;
	}
}
