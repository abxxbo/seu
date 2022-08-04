#include <libc/stdio.h>

#include "../isr.h"
#include "io.h"
#include "shell.h"

#define PROMPT "seu%"

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

char buf[256]; 		// up until an '\n' detected, add to buf
int _append_buf = 0;

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
				putc(chr); // non
				buf[_append_buf] = chr;
				_append_buf++;
				break;
			case 1: // if either are pressed
				putc(chr - 32); // capital
				buf[_append_buf] = (chr - 32);
				_append_buf++;
				break;
		}
	} else {
		switch(ch){
			// Shifts
			case 0x2a: // left shift pressed
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
				printf("\n");

				// Ask shell, if a command that has the first word (sep. by space)
				// in it's list of commands. If anything but a 0 is given, the command
				// either does not exist or is malformed. However, if 2 is given, then 
				// nothing was in the buffer to begin with, so don't do anything
				int ret_code = ask_shell_cmd(buf);
				if(ret_code == 2);
				else if(ret_code != 0) printf("Malformed command and/or unknown command given.\n");
				
				// Clear buffer
				for(int i = 0; i < 256; i++) buf[i] = 0;
				_append_buf = 0;

				printf("%s ", PROMPT);
				break;

			case 0x0e:
				buf[_append_buf] = 0;
				_append_buf--;

				if(x_pos != 0) { 
					wch_pos(0x20, 0x07, 0x00, --x_pos, y_pos);
					update_cursor(x_pos, y_pos);
				}
				break;
		}
	}
}


// register the keyboard handler as a IRQ1
void init_kbd(){
	register_interrupt_handler(IRQ1, &kbd_callback);
}