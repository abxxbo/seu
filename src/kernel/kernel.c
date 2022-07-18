#include <stdio_serial.h>
#include <arch/idt.h>

#include <video/vesa.h>
#include <video/graphics.h>

#define BLUE 0x0000ff
#define GREEN 0x00ff00
#define RED 0xff0000

void kernel_main(){
	init_idt();
	
	draw_rect(20, 20, 20, 20, 0xffffff);
	draw_rect(50, 47, 5, 30, BLUE);
	draw_rect(65, 29, 5, 15, RED);
	draw_rect(52, 84, 20, 20, GREEN);

	for(;;) asm("hlt");
}