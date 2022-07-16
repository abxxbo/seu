#include <libc/stdio.h>

#include <arch/dt.h>
#include <arch/isr.h>


// IRQs
#include <arch/irqs/kbd.h>

void kernel_main(){
	enable_cursor();
	printf("Hello World\n");
	init_dt();
	asm("sti");
	// initialization completed.
	printf("Seu initialization completed!\n");
	// printf("\"balls, nuts, testicles even\"\n\t-- lcohs");

	init_kbd();

	// fix for IRQs
	for(;;) asm("hlt");
}