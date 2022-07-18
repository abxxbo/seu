section .bss
[global vbe_info]
vbe_info:
	.table_data: resb 512-4	;; vbe mode info for mode 0x4118

section .text
MODE equ 0x1115

vbe_init:
	xor ax, ax
	mov es, ax
	
	mov bx, ax
	btr bx, 14
	mov ax, 0x4f01
	mov cx, MODE
	mov di, vbe_info
	int 0x10

	cmp ax, 0x004f
	jne $

	;; since no error occurred, we can just set the video mode
	mov ax, 0x4f02
	mov bx, MODE
	int 0x10
	ret;; no error

