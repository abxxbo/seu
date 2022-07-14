CC := i686-elf-gcc
CFLAGS := -std=gnu99 -ffreestanding -g -Iinclude
LDFLAG := -ffreestanding -nostdlib -g -Tsrc/link.ld

QEMU := qemu-system-i386

QEMU_FLAGS := -no-shutdown -no-reboot -debugcon stdio


all: clean os build_iso
.PHONY: all

run: execute

OBJS := bin/boot.o bin/kernel.o bin/gdt.o bin/idt.o


os:
	@mkdir -p bin/
	@$(CC) $(CFLAGS) -c src/boot/boot.s -o bin/boot.o
	@$(CC) $(CFLAGS) -c src/kernel/kernel.c -o bin/kernel.o
	
	nasm -f elf include/arch/asm/gdt.s -o bin/gdt.o
	nasm -f elf include/arch/asm/interrupts.s -o bin/idt.o
	

	@$(CC) $(LDFLAG) $(OBJS) -o bin/kernel.elf -lgcc

build_iso:
	@mkdir -p isodir/boot/grub
	@cp src/boot/grub.cfg isodir/boot/grub/
	@cp bin/kernel.elf isodir/boot/kernel.elf

	@grub-mkrescue isodir -o seu.iso

execute: seu.iso
	$(QEMU) $(Q_NODEBUG) -cdrom seu.iso

clean:
	rm -rf bin/ isodir/ seu.iso