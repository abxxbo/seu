#include <init.h>
#include <stdio.h>

void kernel_main(){
	init_(0x10000, 0x10000);
	printf("\nHello, World\n");
	for(;;) asm("hlt");
}
