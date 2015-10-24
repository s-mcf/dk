section .text

global _io_write
global _io_read

_io_read:
	mov edx, [esp + 4]
	in al, dx
	ret

_io_write:
	mov edx, [esp + 4]
	mov al, [esp + 8]
	out dx, al
	ret

