#pragma once

void uart_init(void);

int uart_putc(char c);

int uart_getc(void);

void uart_puts(const char* str);

void puts(const char* str);
