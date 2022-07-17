section .bss
[global vbe_mode_info_structure]
vbe_info_structure:
	.table_data: resb 512-4	;; vbe mode info for mode 0x4118

section .text
vbe_init:
	xor ax, ax
	mov es, ax
	
	mov ax, 0x4f01
	mov cx, 0x4118
	mov di, vbe_info_structure
	int 0x10

	cmp ax, 0x004f
	jne $

	;; since no error occurred, we can just set the video mode
	mov ax, 0x4f02
	mov bx, 0x4118
	int 0x10
	ret;; no error

