#include <libc/stdio.h>

#include <arch/dt.h>
#include <arch/isr.h>


// IRQs
#include <arch/irqs/kbd.h>

void kernel_main(){
	printf("Hello World.\n");
	init_dt();
	printf("GDT/IDT Enabled! Testing...\n\n");

	asm("int $0x4");
	asm("int $0xf");

	asm("sti");
	// init_timer(50);
	init_kbd();

	for(;;) asm("hlt");
}