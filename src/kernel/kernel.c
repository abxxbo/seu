#include <stdio_serial.h>
#include <arch/idt.h>

#include <arch/irq/mouse.h>

#include <video/vesa.h>
#include <video/graphics.h>

#define BLUE 0x0000ff
#define GREEN 0x00ff00
#define RED 0xff0000

void kernel_main(){
	init_idt();
	// init_mouse();

	printf("Hello, World\n");
	for(;;) asm("hlt");
}