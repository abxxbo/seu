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
	unsigned volatile where = x * 6 + y * vbe_info.pitch;
	screen[where] = color & 255;
	screen[where + 1] = (color >> 8) & 255;
	screen[where + 2] = (color >> 16) & 255;
}

void kernel_main(){	
	// line
	for(int x = 0; x < vbe_info.width/4; x++){
		putpixel(vbe_info.framebuffer, x, 50, 0xffffff);
	}
	for(;;) asm("hlt");
}