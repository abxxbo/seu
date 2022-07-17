#include <stdio.h>
#include <arch/idt.h>

#include <arch/irq/kb.h>
#include <arch/irq/cmos.h>

#include <mem/paging.h>
#include <mem/mmap/mmap.h>

void kernel_main(){
	// set the first line to a light blue/cyan color
	for(int i = 0; i <= 80; i++) wch_pos(0x20, 0x9, 0x9, i, 0);
	setup_pg();
	printf("\nHello, paging world\n");

	printf("\n\n==== MMAP ENTRIES ====\n");
	g_use_mem();

	// initialize the interrupts
	init_idt();
	init_kbd();
	init_cmos();

	for(;;) asm("hlt");
}