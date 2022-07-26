#include <stdio.h>
#include <init.h>

void kernel_main(){
	init_(0x10000, 0x10000);
	printf("Hello, World\n");
	for(;;) asm("hlt");
}