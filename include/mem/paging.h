#pragma once

#include <libc/stdint.h>

extern void load_page_dir(unsigned int*);
extern void enable_paging();

uint32_t page_directory[1024]__attribute__((aligned(4096)));
uint32_t first_pg_table[1024]__attribute__((aligned(4096)));

void setup_pg(){
	for(int i = 0; i < 1024; i++) page_directory[i] = 0x00000002;
	for(uint32_t j = 0; j < 1024; j++) first_pg_table[j] = (j * 0x1000) | 3;
	page_directory[0] = ((uint32_t)first_pg_table) | 3;

	load_page_dir(page_directory);
	enable_paging();
}