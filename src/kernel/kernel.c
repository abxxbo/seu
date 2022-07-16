#include <libc/stdio.h>
#include <libc/assert.h>

#include <mem/paging.h>

#include <arch/dt.h>
#include <arch/isr.h>

void kernel_main(){
	enable_cursor();

	// initialize interrupts & gdt
	init_dt();
	asm("sti");

	start_paging();
	printf("Hello, paging world!\n");


	// fix for IRQs
	for(;;) asm("hlt");
}