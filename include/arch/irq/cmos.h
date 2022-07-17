#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arch/isr.h>
 

// offset of where the text gets placed
#define OFFSET 72

char second;
char minute;
char hour;
char day;
char month;
unsigned int year;

enum {
	cmos_address = 0x70,
	cmos_data    = 0x71
};
 
int get_update_in_progress_flag() {
	outb(cmos_address, 0x0A);
	return (inb(cmos_data) & 0x80);
}
 
unsigned char get_RTC_register(int reg) {
	outb(cmos_address, reg);
	return inb(cmos_data);
}
 
void cmos_handle() {
	unsigned char century;
	unsigned char last_second;
	unsigned char last_minute;
	unsigned char last_hour;
	unsigned char last_day;
	unsigned char last_month;
	unsigned char last_year;
	unsigned char last_century;
	unsigned char registerB;

	// Note: This uses the "read registers until you get the same values twice in a row" technique
	//       to avoid getting dodgy/inconsistent values due to RTC updates

	while (get_update_in_progress_flag());                // Make sure an update isn't in progress
	second = get_RTC_register(0x00);
	minute = get_RTC_register(0x02);
	hour = get_RTC_register(0x04);
	day = get_RTC_register(0x07);
	month = get_RTC_register(0x08);
	year = get_RTC_register(0x09);

	do {
				last_second = second;
				last_minute = minute;
				last_hour = hour;
				last_day = day;
				last_month = month;
				last_year = year;

				while (get_update_in_progress_flag());           // Make sure an update isn't in progress
				second = get_RTC_register(0x00);
				minute = get_RTC_register(0x02);
				hour = get_RTC_register(0x04);
				day = get_RTC_register(0x07);
				month = get_RTC_register(0x08);
				year = get_RTC_register(0x09);
	} while((last_second != second) || (last_minute != minute) || (last_hour != hour) ||
						(last_day != day) || (last_month != month) || (last_year != year));

	registerB = get_RTC_register(0x0B);

	// Convert BCD to binary values if necessary

	if (!(registerB & 0x04)) {
				second = (second & 0x0F) + ((second / 16) * 10);
				minute = (minute & 0x0F) + ((minute / 16) * 10);
				hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
				day = (day & 0x0F) + ((day / 16) * 10);
				month = (month & 0x0F) + ((month / 16) * 10);
				year = (year & 0x0F) + ((year / 16) * 10);
	}

	// print the time
	if(itos(minute, 10)[1] == 0){
		wch_pos('0', 0xf, 0x9, OFFSET, 0);
		wch_pos(itos(hour, 10)[0], 0xf, 0x9, OFFSET+1, 0);
	} else {
		wch_pos(itos(hour, 10)[0], 0xf, 0x9, OFFSET, 0);
		wch_pos(itos(hour, 10)[1], 0xf, 0x9, OFFSET+1, 0);
	}
	wch_pos(':', 0xf, 0x9, OFFSET+2, 0);
	if(itos(minute, 10)[1] == 0){
		wch_pos('0', 0xf, 0x9, OFFSET+3, 0);
		wch_pos(itos(minute, 10)[0], 0xf, 0x9, OFFSET+4, 0);
	} else {
		wch_pos(itos(minute, 10)[0], 0xf, 0x9, OFFSET+3, 0);
		wch_pos(itos(minute, 10)[1], 0xf, 0x9, OFFSET+4, 0);
	}
	wch_pos(':', 0xf, 0x9, OFFSET+5, 0);
	if(itos(second, 10)[1] == 0){
		wch_pos('0', 0xf, 0x9, OFFSET+6, 0);
		wch_pos(itos(second, 10)[0], 0xf, 0x9, OFFSET+7, 0);
	} else {
		wch_pos(itos(second, 10)[0], 0xf, 0x9, OFFSET+6, 0);
		wch_pos(itos(second, 10)[1], 0xf, 0x9, OFFSET+7, 0);
	}
}

void init_cmos(){
	register_interrupt_handler(IRQ0, &cmos_handle);
}