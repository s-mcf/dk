set -e

mkdir -p build/iso/boot/grub

nasm -felf32 boot/boot.asm -o build/boot.o

i686-elf-gcc -c core/kernel.c -o build/kernel.o -ffreestanding -Wall --std=c11
i686-elf-gcc -c arch/x86.c -o build/x86.o -ffreestanding -Wall --std=c11

i686-elf-gcc -T link.ld -o build/image.elf -ffreestanding -nostdlib build/boot.o build/kernel.o build/x86.o -lgcc

cd build
cp image.elf iso/boot
cp ../grub/grub.cfg iso/boot/grub
grub-mkrescue -d /usr/lib/grub/i386-pc/ -o dk.iso iso
