#pragma once

#include <stddef.h>
#include <stdint.h>

#include <libc/stdio.h>
#include "io.h"

#define IRQ0  32
#define IRQ1  33
#define IRQ2  34
#define IRQ3  35
#define IRQ4  36
#define IRQ5  37
#define IRQ6  38
#define IRQ7  39
#define IRQ8  40
#define IRQ9  41
#define IRQ10  42
#define IRQ11  43
#define IRQ12  44
#define IRQ13  45
#define IRQ14  46
#define IRQ15  47

typedef struct registers {
	uint32_t ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
} registers_t;
typedef void (*isr_t)(registers_t);

isr_t interrupt_handlers[256];
void register_interrupt_handler(uint8_t n, isr_t handler){
	interrupt_handlers[n] = handler;
}

void isr_handler(registers_t regs){
	if(regs.int_no == 0xE) page_fault(regs);
	// else {
		printf("Exception caught. Int No: %x.\n", regs.int_no);
		printf("At the time of the exception...\n");
		printf("EAX was %x, EBX was %x, ECX was %x, EDX was %x.\n", regs.eax, regs.ebx, regs.ecx, regs.edx);
	// }
	asm("cli; hlt");
}

void irq_handler(registers_t regs){
	// EOI to PIC if interrupt involved slave
	if(regs.int_no >= 40) outb(0xa0, 0x20);

	// send signal to master
	outb(0x20, 0x20);

	if(interrupt_handlers[regs.int_no] != 0){
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
}