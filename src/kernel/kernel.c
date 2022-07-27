#include <stdio.h>
#include <init.h>

#include <drivers/floppy.h>

void kernel_main(){
	init_(0x10000, 0x10000);
	printf("\nHello, World\n");
	for(;;) asm("hlt");
}