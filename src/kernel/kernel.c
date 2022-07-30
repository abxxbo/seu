#include <stdio.h>
#include <init.h>

#include "multiboot.h"

void kernel_main(multiboot_info_t* mbd, uint32_t magic){
	// do not initialize seu if magic number is
	// not 0x2badb002. We check this to prove if the bootloader
	// is multiboot1 compliant.
	if(magic != 0x2BADB002){
		set_color(0x4);
		printf("Magic number should be 0x1badb002/0x2badb002. Not %x.\n", magic);
		// halt the computer
		for(;;) asm("1: jmp 1b");
	}

	// Good -- we can initialize everything and
	//		   do OS stuff.

	init_(0x10000, 0x10000);
	printf("\nHello, World\n");
	for(;;) asm("hlt");
}
