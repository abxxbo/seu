#pragma once

#include <arch/idt.h>
#include <arch/isr.h>

// ask FDC for drives
static const char* drive_types[] = {
	"none",
	"360kB 5.25\"",
	"1.2MB 5.25\"",
	"720kB 3.5\"",
	"1.44MB 3.5\"",
	"2.88MB 3.5\"",
	"unknown",
	"unknown"
};

void detect_floppies(){
	// use CMOS
	outb(0x70, 0x10);
	unsigned drives = inb(0x71);

	printf("Floppies detected:\n");
	printf("\tFloppy 0: %s\n", drive_types[drives >> 4]);
	printf("\tFloppy 1: %s\n", drive_types[drives & 0xf]);
}