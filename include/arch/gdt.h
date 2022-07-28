#pragma once

#include <libc/stdint.h>

struct gdt_entry_struct {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t  base_middle;
	uint8_t  access;
	uint8_t  granularity;
	uint8_t  base_high;
}__attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct {
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;


// asm
extern void gdt_flush(uint32_t);

static void gdt_set_gate(int, uint32_t, uint32_t, uint8_t, uint8_t);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

void init_gdt(){
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_ptr.base  = (uint32_t)&gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9a, 0xcf);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xcf);

	// user mode
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xfa, 0xcf);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xf2, 0xcf);

	gdt_flush((uint32_t)&gdt_ptr);
}

static void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity){
	gdt_entries[num].base_low     = (base & 0xFFFF);
	gdt_entries[num].base_middle  = (base >> 16) & 0xFF;
	gdt_entries[num].base_high	  = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low	  = (limit & 0xFFFF);
	gdt_entries[num].granularity  = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= granularity & 0xF0;
	gdt_entries[num].access			  = access;
}
