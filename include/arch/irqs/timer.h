#include "../isr.h"

#include <libc/stdio.h>
#include "io.h"

uint32_t tick = 0;

static void timer_callback(registers_t regs){
	tick++;
	printf("Ticked! %d\n", tick);
}

void init_timer(uint32_t frequency){
	register_interrupt_handler(IRQ0, &timer_callback);
	uint32_t divisor = 1193180 / frequency;

	// cmd byte
	outb(0x43, 0x36);

	// divisor -- sent byte wise
	uint8_t l = (uint8_t)(divisor & 0xFF);
	uint8_t h = (uint8_t)((divisor>>8) & 0xff);

	// send freq div
	outb(0x40, l);
	outb(0x40, h);
}