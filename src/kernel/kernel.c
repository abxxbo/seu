#include <libc/stdio.h>

#include <arch/dt.h>
#include <arch/isr.h>

#include <mmap/mmap.h>
#include <mmap/multiboot.h>


void kernel_main(multiboot_info_t* mb_info, uint32_t magic){
	enable_cursor();
	printf("Hello World!\n");
	
	// initialize interrupts & gdt
	init_dt();
	asm("sti");

	dmm(mb_info, magic);

	// fix for IRQs
	for(;;) asm("hlt");
}