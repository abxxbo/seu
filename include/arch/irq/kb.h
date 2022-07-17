#pragma once

#include <stdio.h>
#include <stdint.h>
#include <arch/isr.h>

void kbd_handler(registers_t regs){
	uint8_t k = inb(0x60);
	printf("Keyboard input achieved\n");
}

void init_kbd(){
	register_interrupt_handler(IRQ1, &kbd_handler);
}