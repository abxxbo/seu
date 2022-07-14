#include <libc/stdio.h>

#include <arch/dt.h>
#include <arch/isr.h>


// IRQs
#include <arch/irqs/kbd.h>

void kernel_main(){
	// disable cursor
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);

	printf("Hello World!\n");
	init_dt();
	printf("GDT/IDT Enabled!\n\n");

	asm("sti");
	// init_timer(50);
	init_kbd();

	for(;;) asm("hlt");
}