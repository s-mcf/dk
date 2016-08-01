set -e
cd "$(dirname "$0")"
CFLAGS="-c -ffreestanding -Wall --std=c11 -I . -I dlibc/ -g"

mkdir -p build/iso/boot/grub

nasm -felf32 boot/boot.asm -o build/boot.o
nasm -felf32 arch/x86/io.asm -o build/io.o
nasm -felf32 arch/x86/interrupt.asm -o build/_interrupt.o
nasm -felf32 arch/x86/keyboard.asm -o build/_keyboard.o
nasm -felf32 arch/x86/gdt.asm -o build/_gdt.o

i686-elf-gcc $CFLAGS core/kernel.c -o build/kernel.o
i686-elf-gcc $CFLAGS arch/x86/video.c -o build/video.o
i686-elf-gcc $CFLAGS arch/x86/interrupt.c -o build/interrupt.o
i686-elf-gcc $CFLAGS arch/x86/keyboard.c -o build/keyboard.o
i686-elf-gcc $CFLAGS arch/x86/gdt.c -o build/gdt.o

i686-elf-gcc $CFLAGS dlibc/string.c -o build/string.o

i686-elf-gcc -T link.ld -o build/image.elf -ffreestanding -nostdlib build/boot.o build/kernel.o build/video.o build/interrupt.o build/_interrupt.o build/io.o build/keyboard.o build/_keyboard.o  build/string.o build/gdt.o build/_gdt.o -lgcc

cd build
cp image.elf iso/boot
cp ../grub/grub.cfg iso/boot/grub
grub-mkrescue -d /usr/lib/grub/i386-pc/ -o dk.iso iso
