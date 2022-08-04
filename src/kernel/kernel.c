#include <stdio.h>
#include <init.h>

#include <fs/fs.h>
#include <fs/initrd.h>

#include <mem/mmap/mmap.h>
#include "multiboot.h"

uint32_t placement_address;

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
	get_mmap(mbd, magic);

	// initialise initrd
	uint32_t initrd_loc = *((uint32_t*)mbd->mods_addr);
	uint32_t initrd_end = *(uint32_t*)(mbd->mods_addr+4);
	placement_address = initrd_end;
	fs_root = initialise_initrd(initrd_loc);

	mem_init(0x10000, 0x10000);

	// init rd is on!
	int i = 0;
	struct dirent *node = 0;
	while ( (node = readdir_fs(fs_root, i)) != 0)
	{
		printf("Found file ");
		printf(node->name);
		fs_node_t *fsnode = finddir_fs(fs_root, node->name);

		if ((fsnode->flags&0x7) == FS_DIRECTORY) printf("\n\t(directory)\n");
		else {
			printf("\n\t contents: \"");
			char buf[256];
			uint32_t sz = read_fs(fsnode, 0, 256, buf);
			printf("%d\n", sz);
			int j;
			for (j = 0; j < sz; j++)
				putc(buf[j]);

			printf("\"\n");
		}
		i++;
	} 
	
	printf("\nHello, World\n");
	
	for(;;) asm("hlt");
}
