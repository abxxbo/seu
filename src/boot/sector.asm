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

;; Check if the disk is a floppy or hard disk
xor dl, dl
mov ah, 15h
int 0x13

;; Do some checks
cmp ah, 0 ;; No drive
je $      ;; Do not boot

cmp ah, 2 ;; Floppy
jle boot_floppy
jg  boot_hdd    ;; it is a hard drive

jmp $
;; Warning, this is only for floppies,
;; Fix for release?
K_LOC equ 0x8000

disk_read_floppy:
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

disk_read_hdd:
  mov ah, 0x02
  mov bx, K_LOC
  mov al, 32
  mov dl, [HDD]
  mov ch, 0x00
  mov dh, 0x00
  mov cl, 0x02

  int 0x13

  jc .failed_read
  ret
  .failed_read:
    jmp $

BDISK: db 0
HDD:   db 0x80

boot_floppy:
  mov [BDISK], dl
  call disk_read_floppy
  jmp K_LOC
  ret       ;; we really won't get here but eh

;; i dont even know if this works
;; on qemu
boot_hdd:
  mov [HDD], dl
  call disk_read_hdd
  jmp K_LOC
  ret

times 510-($-$$) db 0
dw 0xaa55