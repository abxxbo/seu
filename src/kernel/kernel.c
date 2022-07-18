#include <stdio.h>
#include <arch/idt.h>

#include <arch/irq/kb.h>
#include <arch/irq/cmos.h>

#include <mem/paging.h>
#include <mem/mmap/mmap.h>

#include <video/vesa.h>

#define BLUE 0x0000ff
#define GREEN 0x00ff00
#define RED 0xff0000

// unsigned char* screen = vbe_info_structure.framebuffer;
static void putpixel(unsigned char* screen, int x,int y, int color) {
	unsigned where = x * 6 + y * vbe_info_structure.pitch;
	screen[where] = color & 255;
	screen[where + 1] = (color >> 8) & 255;
	screen[where + 2] = (color >> 16) & 255;
}

void kernel_main(){	

	// interesting pattern
	for(int i = 0; i < 27; i++){
		for(int j = 0; j < i; j++){
			if(i %2 == 0) putpixel(vbe_info_structure.framebuffer, i, j, GREEN);
			if(i %3 == 0) putpixel(vbe_info_structure.framebuffer, i, j, RED);
			else { putpixel(vbe_info_structure.framebuffer, i, j, BLUE);}
			i++;
		}
	}
	for(;;) asm("hlt");
}