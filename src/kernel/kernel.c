#include <stdio.h>
#include <arch/idt.h>

#include <arch/irq/kb.h>
#include <arch/irq/cmos.h>

#include <mem/paging.h>
#include <mem/kheap.h>

void kernel_main(){
	// set the first line to a light blue/cyan color
	setup_pg();
	printf("Hello, paging world\n\n\n");

	InitializeHeap(0x100000, 0x100000);

	// initialize the interrupts
	init_idt();
	init_kbd();
	init_cmos();

	for(;;) asm("hlt");
}