[org 0x7c00]
;; Set up segmentation
xor ax, ax
mov ds, ax
mov es, ax


;; Set the video mode.
;; This also clears the screen.
;; This is also called in extended.asm, just to make sure.
mov ah, 0x00
mov al, 0x3
int 0x10

mov bx, boot
call printf

mov ah, 0x86
mov cx, 10
int 0x15

;; Now boot the kernel
mov [BDISK], dl
call disk_read
jmp K_LOC

jmp $
boot: db `Booting to SEU from Floppy...`, 0

;; Warning, this is only for floppies,
;; Fix for release?
K_LOC equ 0x8000

disk_read:
  mov ah, 0x02
  mov bx, K_LOC
  mov al, 32
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


;; BX -> string (input)
printf:
  push ax
  push ax
    mov ah, 0eh
  .Loop:
    cmp [bx], byte 0
    je .Exit

    mov al, [bx]
    int 0x10

    inc bx
    jmp .Loop
  .Exit:
    pop ax
    pop bx
    ret


times 510-($-$$) db 0
dw 0xaa55