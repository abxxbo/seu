#include <libc/stdio.h>

#include "../isr.h"
#include "io.h"

const char sc_table[] ={
	0, 0, '1', '2',
	'3', '4', '5', '6',
	'7', '8', '9', '0',
	'-', '=', 0, 0,
	'q', 'w', 'e', 'r',
	't', 'y', 'u', 'i',
	'o', 'p', '[', ']',
	0, 0, 'a', 's',
	'd', 'f', 'g', 'h',
	'j', 'k', 'l', ';',
	'\'', '`', 0, '\\',
	'z', 'x', 'c', 'v',
	'b', 'n', 'm', ',',
	'.', '/', 0, '*',
	0, ' '
};

void kbd_callback(registers_t regs){
	uint8_t ch = inb(0x60);
	uint8_t chr = 0;
	
	if(ch < 0x3a){ // printable
		chr = sc_table[ch];
	}

	// handle the keyboard
	if(chr != 0){
		term_putc(chr);
	} else {
	}
}


// register the keyboard handler as a IRQ1
void init_kbd(){
	register_interrupt_handler(IRQ1, &kbd_callback);
}