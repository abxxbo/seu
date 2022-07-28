#pragma once

/* other */
#include <libc/stdint.h>
#include <libc/stdio.h>

/* memory */
#include <mem/kheap.h>
#include <mem/paging.h>

/* hardware interrupts */
#include <arch/irq/cmos.h>
#include <arch/irq/kb.h>
#include <arch/isr.h>
#include <arch/idt.h>

#include <drivers/floppy.h>

// initialize the interrupts
void init_ints(){
	init_idt();
	kprintf(SUCCESS, "IDT Started");

	init_cmos();
	init_kbd();
	kprintf(SUCCESS, "KBD and CMOS' Interrupts Registers.");
}

// initialize heap  /  paging
void mem_init(uint32_t heap_start, uint32_t heap_len){
	setup_pg();
	kprintf(SUCCESS, "Initialized paging");
	InitializeHeap(heap_start, heap_len);
	kprintf(SUCCESS, "Heap started.");
}
void init_(uint32_t heap_start, uint32_t heap_len){
	mem_init(heap_start, heap_len);
	init_ints();

	kprintf(SUCCESS, "Seu has initialized itself!\n");
	detect_floppies();
}
