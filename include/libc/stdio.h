#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "vga.h"
#include "string.h"

void term_init(){
	for (int col = 0; col < VGA_COLS; col++){
		for (int row = 0; row < VGA_ROWS; row++){
			// The VGA textmode buffer has size (VGA_COLS * VGA_ROWS).
			// Given this, we find an index into the buffer for our character
			const size_t index = (VGA_COLS * row) + col;
			// Entries in the VGA buffer take the binary form BBBBFFFFCCCCCCCC, where:
			// - B is the background color
			// - F is the foreground color
			// - C is the ASCII character
			vga_buffer[index] = ((uint16_t)y_posor << 8) | ' ';
		}
	}
}

static void scroll(){
	uint8_t attributeByte = (0 << 4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attributeByte << 8);

	if(y_pos >= 25){
			int i;
			for (i = 0*80; i < 24*80; i++){
					vga_buffer[i] = vga_buffer[i+80];
			}

			for (i = 24*80; i < 25*80; i++){
					vga_buffer[i] = blank;
			}
			y_pos = 24;
	}
} 

void term_putc(char c){
	switch (c){
		case '\n': {
			y_pos = 0;
			x_pos++;
			break;
		}
	
		default: {
			const size_t index = (VGA_COLS * x_pos) + y_pos;
			vga_buffer[index] = ((uint16_t)y_posor << 8) | c;
			y_pos++;
			break;
		}
	}
 
	if (y_pos >= VGA_COLS){
		scroll(); // scroll if y >= 25
	}
 
	if (x_pos >= VGA_ROWS){
		y_pos = 0;
		x_pos = 0;
	}
}
 
void puts(const char* str){
	for (size_t i = 0; str[i] != '\0'; i++) term_putc(str[i]);
}

void printf(char* fmt, ...) {
  va_list ap;
	va_start(ap, fmt);

	char* ptr;

	for (ptr = fmt; *ptr != '\0'; ++ptr) {
		if (*ptr == '%') {
			++ptr;
			switch (*ptr) {
				case 's': // string
					puts(va_arg(ap, char*));
					break;

				case 'x': // hex
					// pet peeve,-- no 0x behind hex numbers
					puts("0x");
					puts(convert(va_arg(ap, unsigned int), 16));
					break;

				case 'd': // number
					puts(convert(va_arg(ap, int), 10));
					break;
			}
		} else {
			char terminated[2] = {*ptr, 0};
			puts(terminated);
		}
	}
}