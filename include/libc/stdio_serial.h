/* stdio_serial.h: write to QEMU's serial output. */
#pragma once

#include <stdarg.h>

#include <libc/stdint.h>
#include <libc/string.h>
#include <io.h>

#define SERIAL_OUT 0xe9

// write a character to serial
void sputc(char c){
	outb(SERIAL_OUT, c);
}

// print a string to serial
void sputs(char* s){
	for(; *s != 0; *s++) sputc(*s);
}

// a printf implementation for the serial
void sprintf(char* fmt, ...){
	va_list ap;
	va_start(ap, fmt);

	char* ptr;
	for (ptr = fmt; *ptr != '\0'; ++ptr) {
		if (*ptr == '%') {
			++ptr;
			switch (*ptr) {
				case STR:	// string
					sputs(va_arg(ap, char*));
					break;
				case INT: // integer
					sputs(itos(va_arg(ap, int), 10));
					break;
				case HEX: // hexadecimal
					sputs(itos(va_arg(ap, uint32_t), 16));
					break;
			}
		} else {
			char t[2] = { *ptr, 0 };
			sputs(t);
		}
	}
}