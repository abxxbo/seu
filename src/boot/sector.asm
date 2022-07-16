[org 0x7c00]
;; Set up segmentation
xor ax, ax
mov ds, ax
mov es, ax

mov sp, 0x7c00
mov bp, sp

mov [BDISK], dl
call disk_read
jmp K_LOC

jmp $

;; Warning, this is only for floppies,
;; Fix for release?
K_LOC equ 0x7e00

disk_read:
  mov ah, 0x02
  mov bx, K_LOC
  mov al, 4
  mov dl, [BDISK]
  mov ch, 0x00
  mov dh, 0x00
	mov cl, 0x02

  int 0x13

  jc .failed_read
  ret
	.failed_read:
		jmp $

BDISK: db 0


times 510-($-$$) db 0
dw 0xaa55