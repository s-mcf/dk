#pragma once

extern void keyboard_handler(void);
extern char _io_read(unsigned short port);
extern void _io_write(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);
