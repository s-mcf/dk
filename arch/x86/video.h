#pragma once

#define _X86_VIDMEM 0xb8000
#define _X86_SCREEN_ROWS 25
#define _X86_SCREEN_COLS 80

typedef enum {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
} x86_colors;

void video_init();
void screen_clear();
void puts(const char* s);
void puts_color(const char *s, x86_colors fg, x86_colors bg);
