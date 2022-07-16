#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "vga.h"
#include "string.h"


void term_putc(char c);

static void scroll(uint8_t color){
	uint8_t attributeByte = (0 << 4) | color;
	uint16_t blank = 0x20 | (attributeByte << 8);

	if(y_pos >= 25){
		int i;
		for (i = 0*80; i < 24*80; i++) vga_buffer[i] = vga_buffer[i+80];
		for (i = 24*80; i < 25*80; i++) vga_buffer[i] = blank;
		y_pos = 24;
	}
} 

int color = 2;
void puts(const char *string) {
  volatile uint8_t *video = (volatile uint8_t*)0xB8000;
  while (*string) {
    switch (*string) {
      case '\n':
        update_cursor(x_pos=0,++y_pos);
				scroll(GREY);
        return;
			case '\t':
				for(int i = 0; i < 8; i++) term_putc(0x20);
				return;
      default:
        video[x_pos*2+y_pos*160] = (3 << 16) + *string++;
        if (++x_pos >= 80) {
          x_pos = 0;
          y_pos++;
        }
        update_cursor(x_pos,y_pos);
    }
  }
}

void term_putc(char c){
	char str[2] = {c, '\0'};
	puts(str);
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

#define panic(x) printf(x); for(;;);