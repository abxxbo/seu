#include <stdio.h>
#include <arch/idt.h>

#include <arch/irq/kb.h>
void kernel_main(){
	printf("Hello Kernel World!\n");

	init_idt();
	asm("sti");

	printf("Initialized the IDT!\n");
	init_kbd();
	for(;;) asm("hlt");
}