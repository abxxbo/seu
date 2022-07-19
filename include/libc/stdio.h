#pragma once

#include <libc/stdint.h>
#include <libc/string.h>
#include "io.h"

#include <stdarg.h>


int x_pos = 0;
int y_pos = 0;

uint8_t color = 0x7;
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;


void scroll();
void printf(char* fmt, ...);

#define set_color(x) color = x
void putc(unsigned char c){
  uint16_t attrib = (0 << 4) | (color & 0x0F);
  volatile uint16_t * where;
  where = (volatile uint16_t *)0xB8000 + (y_pos * 80 + x_pos);
  *where = c | (attrib << 8);
	if(++x_pos >= 80){
		x_pos = 0;
		y_pos++;
	
	}
	update_cursor(x_pos, y_pos);

	if(y_pos >= 25) {
		x_pos = 0;
		scroll();
	}
}

void puts(char* str){
	while(*str){
		if(*str == '\n'){
			x_pos = 0;
			y_pos++;
			*str++;
			scroll();
		} else {
			putc(*str);
			*str++;
		}
	}
	update_cursor(x_pos, y_pos); // eh
}


void wch_pos(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y){
	uint16_t attrib = (backcolour << 4) | (forecolour & 0x0F);
	volatile uint16_t* where;
	where = (volatile uint16_t*)0xB8000 + (y * 80 + x) ;
	*where = c | (attrib << 8);
}

void scroll(){
	uint8_t attributeByte = (0 << 4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attributeByte << 8);

	if(y_pos >= 25){
		int i;
		for (i = 0*80; i < 24*80; i++) vga_buffer[i] = vga_buffer[i+80];

		for (i = 24*80; i < 25*80; i++) vga_buffer[i] = blank;
		y_pos = 24;
	}
}

#define STR  's'
#define INT  'd'
#define HEX  'x'
#define CHAR 'c'

void printf(char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	char* ptr;

	for (ptr = fmt; *ptr != '\0'; ++ptr) {
		if (*ptr == '%') {
			++ptr;
			switch (*ptr) {
				case STR:	// string
					puts(va_arg(ap, char*));
					break;
				case INT: // integer
					puts(itos(va_arg(ap, int), 10));
					break;
				case HEX: // hexadecimal
					puts(itos(va_arg(ap, uint32_t), 16));
					break;
				case CHAR:
					// GCC complains that you can't have 'char'
					// as a type for va_arg, so it must be int
					// char r[2] = { va_arg(ap, int), 0 }; // null terminate it
					putc(va_arg(ap, int));
			}
		} else {
			char t[2] = { *ptr, 0 };
			puts(t);
		}
	}
}