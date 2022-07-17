#pragma once

#include <libc/stdint.h>

int x_pos = 0;
int y_pos = 0;

uint8_t color = 0x7;

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
}

void puts(char* str){
	while(*str){
		if(*str == '\n'){
			x_pos = 0;
			y_pos++;
			*str++;
		} else {
			putc(*str);
			*str++;
		}
	}
}
