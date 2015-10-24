; multiboot
MBALIGN     equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MBALIGN | MEMINFO      ; flags
MAGIC       equ  0x1BADB002             ; magic number
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum
 
section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

; allocate stack 
section .bootstrap_stack, nobits
align 4
stack_bottom:
resb 16384 ; 16kb
stack_top:

; entrypoint 
section .text
global _start
_start:
	mov esp, stack_top
	extern kernel_main
	call kernel_main
	cli
.hang:
	hlt
	jmp .hang
