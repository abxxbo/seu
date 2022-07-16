#pragma once

#include <libc/stdio.h>

enum Operator {
	EQ = 0,		// equal to
	N_EQ,			// not equal to
	GT,				// greater than
	LT,				// less than
	GTE,			// greater than or equal
	LTE,			// less than or equal
};

void assert(void* a, int op, void* b){
	switch(op){
		case EQ:
			if(a != b){
				set_text_color(0x4);
				printf("Failed assert: (%x == %x)\n", a, b);
				set_text_color(0x7);
			} else {
				set_text_color(0x2);
				printf("Assert passed: (%x == %x)\n", a, b);
				set_text_color(0x7);
			}
			break;
		case N_EQ:
			if(a == b){
				set_text_color(0x4);
				printf("Failed assert: (%x != %x)\n", a, b);
				set_text_color(0x7);
			} else {
				set_text_color(0x2);
				printf("Assert passed: (%x != %x)\n", a, b);
				set_text_color(0x7);
			}
			break;
		case GT:
			if(!(a > b)){
				set_text_color(0x4);
				printf("Failed assert: (%x > %x)\n", a, b);
				set_text_color(0x7);
			} else {
				set_text_color(0x2);
				printf("Assert passed: (%x > %x)\n", a, b);
				set_text_color(0x7);
			}
			break;
		case LT:
			if(!(a < b)){
				set_text_color(0x4);
				printf("Failed assert: (%x < %x)\n", a, b);
				set_text_color(0x7);
			} else {
				set_text_color(0x2);
				printf("Assert passed: (%x < %x)\n", a, b);
				set_text_color(0x7);
			}
			break;
		case LTE:
			if(!(a <= b)){
				set_text_color(0x4);
				printf("Failed assert: (%x <= %x)\n", a, b);
				set_text_color(0x7);
			} else {
				set_text_color(0x2);
				printf("Assert passed: (%x <= %x)\n", a, b);
				set_text_color(0x7);
			}break;
		case GTE:
			if(!(a >= b)){
				set_text_color(0x4);
				printf("Failed assert: (%x >= %x)\n", a, b);
				set_text_color(0x7);
			} else {
				set_text_color(0x2);
				printf("Assert passed: (%x >= %x)\n", a, b);
				set_text_color(0x7);
			}
			break;
	}
}