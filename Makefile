CC := i686-elf-gcc
CFLAGS := -std=gnu99 -ffreestanding -g -Iinclude -I.
LDFLAG := -ffreestanding -nostdlib -g -Tsrc/link.ld

QEMU 			:= qemu-system-i386
Q_NODEBUG := -m 512m -debugcon stdio
Q_DEBUG		:= -d int -M smm=off -no-shutdown -no-reboot -monitor stdio


all: clean os
.PHONY: all

run: execute

os:
	mkdir -p bin/
	nasm -f bin -Isrc/boot src/boot/sector.asm -o bin/sector.o
	nasm -f elf -Isrc/boot/ext src/boot/extended.asm -o bin/past.o

	$(CC) $(CFLAGS) -c src/kernel/kernel.c -o bin/kernel.o
	
	ld -melf_i386 -Tsrc/link.ld

	cat bin/sector.o bin/kernel.bin > seu.img

execute: seu.img
	$(QEMU) $(Q_NODEBUG) -fda $^

debug: seu.img
	$(QEMU) $(Q_DEBUG) -fda $^

clean:
	@rm -rf bin/ isodir/ seu.img
