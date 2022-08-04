#pragma once

/* other */
#include <libc/stdint.h>
#include <libc/stdio.h>

/* memory */
#include <mem/kheap.h>
#include <mem/paging.h>
#include <mem/mmap/mmap.h>

/* hardware interrupts */
#include <arch/irq/cmos.h>
#include <arch/irq/kb.h>
#include <arch/isr.h>
#include <arch/idt.h>

/* gdt */
#include <arch/gdt.h>

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
	InitializeHeap(heap_start, heap_len);
}

void init_(){
	init_gdt();
	init_ints();

	kprintf(SUCCESS, "Seu has initialized itself!\n");
}

