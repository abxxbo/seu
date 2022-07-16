#pragma once

#include <libc/stdio.h>

#include "multiboot.h"

void dmm(multiboot_info_t* mbd, uint32_t magic){
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		panic("invalid magic number!"); 
	}
	
	/* Check bit 6 to see if we have a valid memory map */
	if(!(mbd->flags >> 6 & 0x1)){
		panic("invalid memory map given by GRUB bootloader");
	}
	/* Loop through the memory map and display the values */
	int i;
	for(i = 0; i < mbd->mmap_length;  i += sizeof(multiboot_memory_map_t)){
		multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*) (mbd->mmap_addr + i);

		printf("Start Addr: %x | Length: %x | Size: %x | Type: %d\n",
				mmmt->addr, mmmt->len, mmmt->size, mmmt->type);

		if(mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) {
			/* 
				* Do something with this memory block!
				* BE WARNED that some of memory shown as availiable is actually 
				* actively being used by the kernel! You'll need to take that
				* into account before writing to memory!
				*/
		}
	}
}