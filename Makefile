CC := i686-elf-gcc
CFLAGS := -std=gnu99 -ffreestanding -g -Iinclude -Iinclude/libc/
LDFLAG := -Tsrc/link.ld

QEMU 			:= qemu-system-i386
Q_NODEBUG := -m 512m -debugcon stdio
Q_DEBUG		:= -d int -M smm=off -no-shutdown -no-reboot -monitor stdio


OBJS := bin/boot.o bin/kernel.o bin/gdt.o bin/idt.o bin/paging.o bin/task.o

all: clean os
.PHONY: all

run: execute

os:
	mkdir -p bin/
	i686-elf-as src/boot/boot.s -o bin/boot.o


	nasm -f elf include/arch/asm/gdt.s -o bin/gdt.o
	nasm -f elf include/arch/asm/idt.s -o bin/idt.o
	nasm -f elf include/mem/asm/paging.asm -o bin/paging.o

	i686-elf-as include/tasks/asm/task.s -o bin/task.o

	$(CC) $(CFLAGS) -c src/kernel/kernel.c -o bin/kernel.o

	$(CC) -T src/link.ld -o bin/os.bin -ffreestanding -O2 -nostdlib $(OBJS) -lgcc

	mkdir -p isodir/boot/grub
	cp bin/os.bin isodir/boot/os.bin
	cp src/boot/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o seu.iso isodir

execute: seu.iso
	$(QEMU) $(Q_NODEBUG) -cdrom $^

clean:
	rm -rf bin isodir seu.iso
