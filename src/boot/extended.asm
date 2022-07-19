;; Set video mode.
mov ah, 0x00
mov al, 0x03
int 0x10
jmp _pmode

%include "gdt.asm"
%include "detect_memory.asm"
%include "vesa.asm"

_pmode:
	call dmem
	call _a20
	cli
	lgdt [gdt_desc]
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	jmp codeseg:spmode

_a20:
	in al, 0x92
	or al, 2
	out 0x92, al
	ret

[bits 32]
[extern kernel_main]
spmode:
	mov ax, dataseg
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call kernel_main
	jmp $