#include <libc/stdio.h>

#include <arch/dt.h>
#include <arch/isr.h>


// IRQs
#include <arch/irqs/kbd.h>

// other
#include <mem/paging.h>

void kernel_main(){
	enable_cursor();
	printf("Hello World!\n");
	init_dt();
	printf("GDT/IDT Enabled!\n\n");

	asm("sti");
	// init_timer(50);
	initialize_paging();

	// Cause a page fault
	uint32_t *ptr = (uint32_t*)0xA0000000;
	uint32_t do_page_fault = *ptr;

	// fix for IRQs
	for(;;) asm("hlt");
}