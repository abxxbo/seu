;; TODO: set video mode

jmp pmode

%include "gdt.asm"

pmode:
	call _a20
	cli
	lgdt [gdt_desc]
	jmp $

_a20:
	in al, 0x92
	or al, 2
	out 0x92, al
	ret
