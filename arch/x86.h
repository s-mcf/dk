#pragma once

#define _X86_VIDMEM 0xb8000
#define _X86_SCREEN_ROWS 25
#define _X86_SCREEN_COLS 80
#define _X86_SCREEN_GRAYBLACK 0x07

void arch_init();
void screen_clear();
void puts(const char* s);
