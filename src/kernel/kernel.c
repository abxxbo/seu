#include <libc/stdio.h>

#include <arch/dt.h>
#include <arch/isr.h>

void kernel_main(){
	enable_cursor();
	printf("Hello World!\n");
	
	// initialize interrupts & gdt
	init_dt();
	asm("sti");

	// fix for IRQs
	for(;;) asm("hlt");
}