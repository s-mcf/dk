section .data
dstring: db "interrupt asm",0x0

section .text
global keyboard_handler

extern keyboard_handler_main
extern puts

keyboard_handler:                 
	pushad
	call    keyboard_handler_main
	popad
	iret
