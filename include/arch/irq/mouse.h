/* NOTE: This source code is adapted from
 * SANiK's "Free PS/2 mouse code" on the
 * OSDev Forums:
 * https://forum.osdev.org/viewtopic.php?t=10247
*/
#pragma once

#include <libc/stdint.h>
#include <libc/stdio_serial.h>
#include <arch/isr.h>

#include <video/vesa.h>
#include <video/graphics.h>
#include <io.h>

uint8_t mouse_cycle = 0;
char mouse_byte[3];
char mouse_x = 0;
char mouse_y = 0;

void mouse_wait(uint8_t a_type);

void mouse_handler(registers_t* r){
	switch(mouse_cycle){
		case 0:
			mouse_byte[0] = inb(0x60);
			mouse_cycle++;
			break;
		case 1:
			mouse_byte[1] = inb(0x60);
			mouse_cycle++;
			break;
		case 2:
			mouse_byte[2] = inb(0x60);
			mouse_x = mouse_byte[1];
			mouse_y = mouse_byte[2];
			putpixel(vbe_info.framebuffer, mouse_x, mouse_y, YELLOW);
			mouse_cycle = 0;
			break;
	}
	outb(0x20, 0x20); outb(0xA0, 0x20);
}

uint8_t mouse_read(){
	mouse_wait(0);
	return inb(0x60);
}

void mouse_write(uint8_t a_write){
	mouse_wait(1);
	outb(0x64, 0xd4);
	mouse_wait(1);
	outb(0x60, a_write);
}

void mouse_wait(uint8_t a_type){
	uint32_t _time_out = 100000;
	if(a_type == 0){
		while(_time_out--){
			if((inb(0x64) & 1) == 1) return;
		}
		return;
	} else {
		while(_time_out--){
			if((inb(0x64) & 2) == 0) return;
		}
		return;
	}
}

void init_mouse(){
	uint8_t _status;

	mouse_wait(1);
	outb(0x64, 0xa8);

	mouse_wait(1);
	outb(0x64, 0x20);
	mouse_wait(0);
	_status=inb(0x60);         
	_status = (_status | 2) ;
	mouse_wait(1);
	outb(0x64, 0x60);
	mouse_wait(1);
	outb(0x60, _status);


	// use default settings
	mouse_write(0xf6);
	mouse_read();

	// send packets
	mouse_write(0xf4);
	mouse_read();

	register_interrupt_handler(IRQ12, &mouse_handler);
}