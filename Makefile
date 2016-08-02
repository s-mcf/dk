CC=i686-elf-gcc
CFLAGS=-ffreestanding -Wall --std=c11
ASM=nasm

all:
	mkdir -p build/iso/boot/grub
	$(ASM) -felf32 boot/boot.asm -o build/boot.o
	$(CC) -c core/kernel.c -o build/kernel.o $(CFLAGS)
	$(CC) -c arch/x86.c -o build/x86.o $(CFLAGS)
	$(CC) -T link.ld -o build/image.elf -ffreestanding -nostdlib build/boot.o build/kernel.o build/x86.o -lgcc
	cp ./build/image.elf ./build/iso/boot
	cp ./grub/grub.cfg ./build/iso/boot/grub

rescue-partition:
	grub-mkrescue -d /usr/lib/grub/i386-pc/ -o dk.iso iso

clean:
	rm -rf build

.PHONY: all rescue-partition clean
