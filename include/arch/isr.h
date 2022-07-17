#include <libc/stdio.h>
#include <libc/stdint.h>

typedef struct registers
{
	uint32_t ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
} registers_t; 

void isr_handler(registers_t regs){
	set_color(0x4);
	printf("unhandled interrupt 0x%x\n", regs.int_no);
}