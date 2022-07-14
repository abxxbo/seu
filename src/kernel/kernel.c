#include <stddef.h>
#include <stdint.h>

#include <libc/stdio.h>

#include <arch/isr.h>
#include <arch/dt.h>
void kernel_main(){
	printf("Hello World.\n");
	init_dt();
	printf("GDT/IDT Enabled! Testing...\n\n");

	asm("int $0x4");
	asm("int $0xf");	
}