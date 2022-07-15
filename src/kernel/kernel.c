#include <libc/stdio.h>

#include <arch/dt.h>
#include <arch/isr.h>


// IRQs
#include <arch/irqs/kbd.h>

void kernel_main(){
	enable_cursor();
	printf("Hello World!\n");
	init_dt();
	printf("GDT/IDT Enabled!\n\n");

	asm("sti");
	// init_timer(50);
	init_kbd();

	// fix for IRQs
	for(;;) asm("hlt");
}