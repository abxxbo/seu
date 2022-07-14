#pragma once

#include <stddef.h>
#include <stdint.h>

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;
 
int y_pos = 0;
int x_pos = 0;
uint8_t y_posor = 0x0F;