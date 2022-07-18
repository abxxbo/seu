#pragma once

#include <stdio.h>
#include <stdint.h>

#include <video/vesa.h>

// unsigned char* screen = vbe_info_structure.framebuffer;
void putpixel(uint8_t* screen, int x,int y, int color) {
	unsigned volatile where = x * 6 + y * vbe_info.pitch;
	screen[where] = color & 255;
	screen[where + 1] = (color >> 8) & 255;
	screen[where + 2] = (color >> 16) & 255;
}

// draws horizontal line from x1 -> x2, on y position Y with color COLOR
void put_h_line(int x1, int y1, int x2, int color){
	for(; x1 <= x2; x1++) putpixel(vbe_info.framebuffer, x1, y1, color);
}
// draws vertical line from y1 -> y2, on x position X with color COLOR
void put_v_line(int y1, int y2, int x, int color){
	for(; y1 <= y2; y1++) putpixel(vbe_info.framebuffer, x, y1, color);
}

// draws a rectangle from initial x,y to width W, and H, as well 
// as each side has the color of COLOR
void draw_rect(int init_x, int init_y, int w, int h, int color){
	// draw the first vertical / horizontal line
	put_h_line(init_x, init_y, (init_x+w), color);
	put_v_line(init_y, (init_y+h), init_x, color);

	// draw the final lines
	put_h_line(init_x, (init_y+h), (init_x+w), color);
	put_v_line(init_y, (init_y+h), (init_x+w), color);
}