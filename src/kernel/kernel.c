#include <stdio.h>
#include <arch/idt.h>
void kernel_main(){
	printf("Hello Kernel World!\n");

	init_idt();
	printf("Initialized the IDT!\n");
}