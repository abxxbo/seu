#pragma once

#include <stddef.h>
#include <stdint.h>

extern void load_pg_dir(uint32_t*);
extern void enable_paging();

void clear_out_pdir(uint32_t* page_dir);
void fill_tbleone(uint32_t* table);

uint32_t page_dir[1024]		 		__attribute__((aligned(4096)));
uint32_t one_page_table[1024] __attribute__((aligned(4096)));

void clear_out_pdir(uint32_t* page_dir){
	for(int i = 0; i < 1024; i++){
		// Sets the directory to be:
		//		- Supervisor (kernel-mode only)
		//		- RW Enabled (read/write)
		//		- Not Present (it does not exist)
		page_dir[i] = 0x00000002;
	}
}

// fill the first page table
void fill_tbleone(uint32_t* table){
	uint32_t i;
	for(i = 0; i < 1024; i++){
		// 12 bits will be zeroed,
		// those are for attributes
		one_page_table[i] = (i * 0x1000) | 3;
		// Gives each entry these attributes:
		//	- supervisor
		//	- read/write
		//	- present		 (it exists)
	}
	// set page_dir[0] to the first table
	page_dir[0] = ((uint32_t)one_page_table) | 3;
}

void start_paging(){
	clear_out_pdir(page_dir);
	fill_tbleone(one_page_table);
	load_pg_dir(page_dir);
	enable_paging();
}