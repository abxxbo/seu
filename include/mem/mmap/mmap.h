#pragma once

#include <stdio.h>
#include <stdint.h>
#include <multiboot.h>

void get_mmap(multiboot_info_t* info, uint32_t magic){
	// We don't need to check for the magic number -- we
	// already did that

	// check bit 6 for valid mmap
	if(!(info->flags >> 6 & 0x1)) printf("Invalid MMap given by GRUB!");

	// first thing to do is to is change the color
	printf("Memory map:\n");
	set_color(0x9);
	
	// print memory map content
	for(int i = 0; i < info->mmap_length; i += sizeof(multiboot_memory_map_t)){
		multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*)(info->mmap_addr + i);
		printf("Start addr -> %x | Length: %x | Size: %x | Type: %d\n",
				mmmt->addr, mmmt->len, mmmt->size, mmmt->type);
	}

	// set the color back to normal
	set_color(0x7);
}
