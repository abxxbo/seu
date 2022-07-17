#include <stdio.h>
#include <arch/idt.h>

#include <arch/irq/kb.h>
#include <arch/irq/cmos.h>

void kernel_main(){
	// set the first line to a light blue/cyan color
	for(int i = 0; i <= 80; i++) wch_pos(0x20, 0x9, 0x9, i, 0);
	printf("\nHello Kernel World!\n");

	init_idt();
	asm("sti");

	// initialize the interrupts
	init_kbd();
	init_cmos();

	for(;;) asm("hlt");
}