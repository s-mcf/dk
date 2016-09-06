set -e
set -x
cd "$(dirname "$0")"
CFLAGS="-c -mcpu=arm1176jzf-s -fpic -ffreestanding -std=c11  -O2 -Wall -Wextra -Werror -I . -I dlibc -g"

mkdir -p build
arm-none-eabi-gcc $CFLAGS boot/arm/boot.S -o build/boot.o
arm-none-eabi-gcc $CFLAGS core/kernel.c -o build/kernel.o
arm-none-eabi-gcc $CFLAGS arch/arm/uart.c -o build/uart.o
arm-none-eabi-gcc -T ./arch/arm/link.ld -o build/dk.elf -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o build/uart.o

# Run with qemu-system-arm -kernel build/dk.elf -no-reboot  -serial stdio -M raspi2
