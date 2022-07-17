#pragma once

#include <stdio.h>
#include <stdint.h>

#define MMAP_USABLE   1
#define MMAP_RESERVED 2


typedef struct {
	uint64_t base_addr;
	uint64_t region_len;
	uint32_t region_type;
	uint32_t ext_attr;
} mmap_entry_t;

extern uint8_t reigon_ct;
uint8_t usable_region_ct;
mmap_entry_t* u_mem_regs[10];

uint8_t reserved_region_ct;
mmap_entry_t* r_mem_regs[10];

int mm_reg_got = 0;


// get the usable memory regions
mmap_entry_t** g_use_mem(){
	if(mm_reg_got) return u_mem_regs;
	uint8_t u_reg_index;
	for(uint8_t i = 0; i < reigon_ct; i++){
		mmap_entry_t* mmap = (mmap_entry_t*)0x5000;
		mmap += i;
		if(mmap->region_type == MMAP_USABLE){
			set_color(0xa);
			printf("Entry %d is usable.\n", i);
			set_color(0x7);
			u_mem_regs[u_reg_index] = mmap;
			u_reg_index++;
		} else {
			set_color(0xc);
			printf("Entry %d is reserved.\n", i);
			set_color(0x7);
		}
	}
	reigon_ct = u_reg_index;
	mm_reg_got = 1;
	return u_mem_regs;
}