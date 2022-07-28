#pragma once

#include <stdio.h>
#include <stdint.h>
#include <arch/isr.h>

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


int lshift = 0;
int rshift = 0;

char* buffer;
int _buf = 0;

void kbd_handler(registers_t regs){
	uint8_t k = inb(0x60); // ask CPU for port 0x60 -- keyboard
	uint8_t c = 0;				 // we look up the chracter in the lookup table
	if(k < 0x3a){
		c = sc_table[k];
	}

	// check some cases
	if(c != 0){
		// check shift
		switch(lshift | rshift){
			case 1: // capitalized letters
			buffer[_buf] = (c-32);
				_buf++;
				putc(c - 32);
				break;
			case 0: // lowercase
				buffer[_buf] = c;
				_buf++;
				putc(c);
				break;
		}
	} else {
		// other
		switch(k){
			case 0x2a: // left shift, pressed
				lshift = 1;
				break;
			case 0xaa: // left shift, released
				lshift = 0;
				rshift = 0;
				break;

			// the same thing for the right shift
			case 0x36:
				rshift = 1;
				break;
			case 0xb6:
				lshift = 0;
				rshift = 0;
				break;

			// newline
			case 0x9c:
				printf("\n");
		}
	}
}

void init_kbd(){
	register_interrupt_handler(IRQ1, &kbd_handler);
}
