#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "uart.h"
#include "mmio.h"

#define BCM_PERIPH_BASE_PHYS (0x3f000000U)
#define UART0_BASE (BCM_PERIPH_BASE_PHYS + 0x201000)

#define UART_DR    (0x00)
#define UART_RSR   (0x04)
#define UART_TFR   (0x18)
#define UART_ILPR  (0x20)
#define UART_IBRD  (0x24)
#define UART_FBRD  (0x28)
#define UART_LCRH  (0x2c)
#define UART_CR    (0x30)
#define UART_IFLS  (0x34)
#define UART_IMSC  (0x38)
#define UART_TRIS  (0x3c)
#define UART_TMIS  (0x40)
#define UART_ICR   (0x44)
#define UART_DMACR (0x48)

static inline uint32_t uart_reg(uint32_t base, uint32_t reg) {
    return base + reg;
}

void uart_init(void) {
    // clear all irqs
    mmio_write(uart_reg(UART0_BASE, UART_ICR), 0x3ff);

    // set fifo trigger level
    mmio_write(uart_reg(UART0_BASE, UART_IFLS), 0); // 1/8 rxfifo, 1/8 txfifo

    // enable rx interrupt
    mmio_write(uart_reg(UART0_BASE, UART_IMSC), (1<<6)|(1<<4)); // rtim, rxim

    // enable receive
    mmio_or(uart_reg(UART0_BASE, UART_CR), (1<<9)); // rxen
}

int uart_putc(char c) {
    /* spin while fifo is full */
    while (mmio_read(uart_reg(UART0_BASE, UART_TFR)) & (1<<5));
    mmio_write(uart_reg(UART0_BASE, UART_DR), c);

    return c;
}

int uart_getc(void) {
    /* spin while fifo is full */
    while (mmio_read(uart_reg(UART0_BASE, UART_TFR)) & (1<<4));
    return mmio_read(uart_reg(UART0_BASE, UART_DR));
}

void uart_puts(const char* str) {
    for ( size_t i = 0; str[i] != '\0'; i++ ) {
        uart_putc(str[i]);
    }
}

void puts(const char* str) {
    uart_puts(str);
}
