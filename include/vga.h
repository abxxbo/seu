#pragma once

#include <stddef.h>
#include <stdint.h>

#include "io.h"

#define BLUE (1 & 0x0F)
#define GREEN (2 & 0x0F)
#define CYAN (3 & 0x0F)
#define D_RED (4 & 0x0F)
#define MAGENTA (5 & 0x0F)
#define ORANGE (6 & 0x0F)
#define GREY    (7 & 0x0F)
#define D_GREY (8 & 0x0F)
#define L_BLUE (9 & 0x0F)
#define L_GREEN (10 & 0x0F)
#define L_CYAN (11 & 0x0F)
#define RED (12 & 0x0F)
#define L_MAGEN (13 & 0x0F)
#define YELLOW (14 & 0x0F)
#define WHITE (15 & 0x0F)

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;
 
int y_pos = 0;
int x_pos = 0;
uint8_t y_posor = 0x0F;

void enable_cursor(){
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | 0);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | 15);
}

void update_cursor(int x, int y){
	uint16_t pos = y * VGA_COLS + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}