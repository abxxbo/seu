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

void isr_handler(registers_t r){
	int fault = 0;
	int traps = 0;

	switch(r.int_no){
		case 0x0: { fault = 1; break; }
		case 0x1: { traps = 1; fault = 1; break; }
		case 0x3: { traps = 1; fault = 0; break; }
		case 0x4: { traps = 1; break; }
		case 0x5: { fault = 1; break; }
		case 0x6: { fault = 1; break; }
		case 0x7: { fault = 1; break; }
		
		case 0xa: { fault = 1; break; }
		case 0xb: { fault = 1; break; }
		case 0xc: { fault = 1; break; }
		case 0xd: { fault = 1; break; }
		case 0xe: { fault = 1; break; }

		case 0x10: { fault = 1; break; }
		case 0x11: { fault = 1; break; }
		case 0x13: { fault = 1; break; }
		case 0x14: { fault = 1; break; }
		case 0x15: { fault = 1; break; }
		case 0x1c: { fault = 1; break; }
		case 0x1d: { fault = 1; break; }
		case 0x1e: { fault = 1; break; }
		
	}
	if(fault == 1 && traps == 0){
		int ecode = 0;
		if(r.err_code != 0) ecode = 1;
		printf("Fault occurred!\t");
		set_text_color(0xa);
		printf("Int. No: %x. Error code? %s -- %d (%x)\n",
					  r.int_no, ecode ? "Yes": "N/A", r.err_code, r.err_code);
		set_text_color(0x7);
		return; // Return execution to main proc.
	}

	if(fault == 0 && traps == 1){
		int ecode = 0;
		if(r.err_code != 0) ecode = 1;
		printf("Trap occurred!\t ");
		set_text_color(0x2);
		printf("Int. No: %x. Error code? %s -- %d (%x)\n",
					  r.int_no, ecode ? "Yes": "N/A", r.err_code, r.err_code);
		set_text_color(0x7);
		return; // Return execution to main proc.
	}

	if(fault && 1 == traps == 1){
		int ecode = 0;
		if(r.err_code != 0) ecode = 1;
		printf("Trap+Fault occurred!   ");
		set_text_color(0x1);
		printf("Int. No: %x. Error code? %s -- %d (%x)\n",
					  r.int_no, ecode ? "Yes": "N/A", r.err_code, r.err_code);
		set_text_color(0x7);
		return; // Return execution to main proc.
	}

	if(fault && 0 == traps == 0){
		int ecode = 0;
		printf("Unhandled interrupt! ");
		set_text_color(0x4);
		
		if(r.err_code != 0) ecode = 1;
		printf("Int No: %x | Err. Code? %s (val: %x)\n",
						r.int_no, ecode ? "Yes" : "No", r.err_code);
		// Halt computer. Since we check if the interrupt number
		// before, and if it's a fault or trap, we do not halt,
		// just return.

		// Since this is not a fault or trap, we will hang the computer
		asm("cli; hlt");
	}
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