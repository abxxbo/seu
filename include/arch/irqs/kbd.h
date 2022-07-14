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

int lshift_pressed = 0;
int rshift_pressed = 0;

void kbd_callback(registers_t regs){
	uint8_t ch = inb(0x60);
	uint8_t chr = 0;
	
	if(ch < 0x3a){ // printable
		chr = sc_table[ch];
	}

	// handle the keyboard
	if(chr != 0){
		switch(lshift_pressed | rshift_pressed){
			case 0:
				term_putc(chr); // non
				break;
			case 1: // if either are pressed
				term_putc(chr - 32); // capital
				break;
		}
	} else {
		switch(ch){
			// Shifts
			case 0x2a: // left shit pressed
				lshift_pressed = 1;
				break;
			case 0xaa: // left shift released
				lshift_pressed = 0;
				break;

			/// Right shift
			case 0x36: // pressed
				rshift_pressed = 1;
				break;
			case 0xb6: // released
				rshift_pressed = 0;
				break;

			// other important keyboard input
			case 0x9c: // Enter
				puts("\n");
				break;
		}
	}
}


// register the keyboard handler as a IRQ1
void init_kbd(){
	register_interrupt_handler(IRQ1, &kbd_callback);
}