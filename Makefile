CC := i686-elf-gcc
CFLAGS := -std=gnu99 -ffreestanding -g -Iinclude -I.
LDFLAG := -ffreestanding -nostdlib -g -Tsrc/link.ld

QEMU 			:= qemu-system-i386
Q_NODEBUG := -m 512m -debugcon stdio
Q_DEBUG		:= -d int -M smm=off -no-shutdown -no-reboot -monitor stdio


all: clean os #build_iso
.PHONY: all

run: execute

OBJS := bin/boot.o bin/kernel.o bin/gdt.o bin/idt.o


os:
	mkdir -p bin/
	nasm -f bin src/boot/sector.asm -o bin/sector.o
	nasm -f elf -Isrc/boot/ext src/boot/extended.asm -o bin/past.o
	ld -melf_i386 -Tsrc/link.ld

	cat bin/sector.o bin/kernel.bin > kernel.img

build_iso:
	@mkdir -p isodir/boot/grub
	@cp src/boot/grub.cfg isodir/boot/grub/
	@cp bin/kernel.elf isodir/boot/kernel.elf

	@grub-mkrescue isodir -o seu.iso 2>/dev/null

execute: seu.iso
	$(QEMU) $(Q_NODEBUG) -cdrom $^

debug: seu.iso
	$(QEMU) $(Q_DEBUG) -cdrom $^

clean:
	@rm -rf bin/ isodir/ seu.iso
