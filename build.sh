set -e
cd "$(dirname "$0")"
CFLAGS="-c -ffreestanding -Wall --std=c11 -I ."

mkdir -p build/iso/boot/grub

nasm -felf32 boot/boot.asm -o build/boot.o

i686-elf-gcc $CFLAGS core/kernel.c -o build/kernel.o
i686-elf-gcc $CFLAGS arch/x86/video.c -o build/video.o

i686-elf-gcc -T link.ld -o build/image.elf -ffreestanding -nostdlib build/boot.o build/kernel.o build/video.o -lgcc

cd build
cp image.elf iso/boot
cp ../grub/grub.cfg iso/boot/grub
grub-mkrescue -d /usr/lib/grub/i386-pc/ -o dk.iso iso
