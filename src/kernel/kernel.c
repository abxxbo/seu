#include <stdio.h>
#include <arch/idt.h>

#include <arch/irq/kb.h>
#include <arch/irq/cmos.h>

#include <mem/paging.h>
#include <mem/mmap/mmap.h>

#include <video/vesa.h>

void kernel_main(){
	// set the first line to a light blue/cyan color
	for(int i = 0; i <= 80; i++) wch_pos(0x20, 0x9, 0x9, i, 0);

	// setts 
	volatile uint32_t *fb = (uint32_t *)((uint32_t) vbe_info_structure.framebuffer);

	for(;;) asm("hlt");
}