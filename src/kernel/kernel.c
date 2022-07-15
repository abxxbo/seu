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

	uint32_t f = kmalloc(2147483647);
	printf("Kmalloc %x/%d", f, f);
	// fix for IRQs
	for(;;) asm("hlt");
}