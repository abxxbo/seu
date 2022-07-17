#pragma once

#include <libc/stdio.h>
#include <libc/stdint.h>
#include <io.h>

typedef struct regs {
	uint32_t ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
} registers_t; 

typedef void (*isr_t)(registers_t);
void register_interrupt_handler(uint8_t n, isr_t handler); 

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47
isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler){ interrupt_handlers[n] = handler; }

void isr_handler(registers_t regs){
	set_color(0x4);
	printf("unhandled interrupt 0x%x\n", regs.int_no);
	asm("cli; hlt");
}


// irq handler
void irq_handler(registers_t r){
	// send EOI
	if(r.int_no >= 40){
		// it was involved with the slave
		outb(0xa0, 0x20);
	}
	// send signal to master
	outb(0x20, 0x20);

	if(interrupt_handlers[r.int_no] != 0){
		isr_t handler = interrupt_handlers[r.int_no];
		handler(r);
	}
}