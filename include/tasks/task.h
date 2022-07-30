#pragma once

#include <libc/stdio.h>
#include <stdint.h>

typedef struct {
	uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags, cr3;
} Registers;

typedef struct Task {
	Registers regs;
	struct Task* next;
} Task;

void init_tasking();
void create_task(Task*, void(*)(), uint32_t, uint32_t*);

void yield();	// frontend
extern void switch_task(Registers* old, Registers* new);




static Task* running_task;
static Task  main_task;
static Task  other_task;

static void other_main(){}

void init_tasking(){
	asm volatile("movl %%cr3, %%eax; mov %%eax, %0" : "=m"(main_task.regs.cr3) :: "%eax");
	asm volatile("pushfl; movl (%%esp), %%eax; movl %%eax, %0; popfl;" : "=m"(main_task.regs.eflags) :: "%eax");

	create_task(&other_task, other_main, main_task.regs.eflags, (uint32_t*)main_task.regs.cr3);
	main_task.next = &other_task;
	other_task.next = &main_task;

	running_task = &main_task;
}

void create_task(Task* task, void (*main)(), uint32_t flags, uint32_t* pagedir){
	task->regs.eax = 0;
	task->regs.ebx = 0;
	task->regs.ecx = 0;
	task->regs.edx = 0;
	task->regs.esi = 0;
	task->regs.edi = 0;
	task->regs.eflags = flags;
	task->regs.eip = (uint32_t) main;
	task->regs.cr3 = (uint32_t) pagedir;
	task->regs.esp = (uint32_t) 0x10000; // definently broken
	task->next = 0;
}

void yield(){
	Task* last = running_task;
	running_task = running_task->next;
	switch_task(&last->regs, &running_task->regs);
}

void make_task(void (*fn)()){
	asm volatile("movl %%cr3, %%eax; mov %%eax, %0" : "=m"(main_task.regs.cr3) :: "%eax");
	asm volatile("pushfl; movl (%%esp), %%eax; movl %%eax, %0; popfl;" : "=m"(main_task.regs.eflags) :: "%eax");

	create_task(&other_task, fn, main_task.regs.eflags, (uint32_t*)main_task.regs.cr3);
	main_task.next = &other_task;
	other_task.next = &main_task;

	running_task = &main_task;
	// switch to said task
	switch_task(&running_task->regs, &running_task->regs);
}
