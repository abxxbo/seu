#include <arch/isr.h>
#include <libc/stdio.h>

#include "kheap.h"


typedef struct page {
	uint32_t present : 1;
	uint32_t rw : 1;			// read only if clear
	uint32_t user : 1;
	uint32_t accessed : 1;
	uint32_t dirty : 1;
	uint32_t unused : 7;
	uint32_t frame : 20;
} page_t;

typedef struct page_table {
	page_t pages[1024];
} page_table_t;

typedef struct page_directory {
	page_table_t* tables[1024]; // arr of ptrs to pagetables
	uint32_t phys_tables[1024]; // physical location of pagetables
	uint32_t phys_addr; // physical address of phys_addr
} page_directory_t;

void switch_page_directory(page_directory_t *new);
page_t *get_page(uint32_t address, int make, page_directory_t *dir);
void page_fault(registers_t regs);

uint32_t *frames;
uint32_t nframes;
extern uint32_t placement_address;

page_directory_t* current_directory;
page_directory_t* kernel_directory;

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))



static void set_frame(uint32_t frame_addr){
  uint32_t frame = frame_addr/0x1000;
  uint32_t idx = INDEX_FROM_BIT(frame);
  uint32_t off = OFFSET_FROM_BIT(frame);
  frames[idx] |= (0x1 << off);
}

static void clear_frame(uint32_t frame_addr){
  uint32_t frame = frame_addr/0x1000;
  uint32_t idx = INDEX_FROM_BIT(frame);
  uint32_t off = OFFSET_FROM_BIT(frame);
  frames[idx] &= ~(0x1 << off);
}

static uint32_t test_frame(uint32_t frame_addr){
  uint32_t frame = frame_addr/0x1000;
  uint32_t idx = INDEX_FROM_BIT(frame);
  uint32_t off = OFFSET_FROM_BIT(frame);
  return (frames[idx] & (0x1 << off));
}

static uint32_t first_frame(){
  uint32_t i, j;
  for (i = 0; i < INDEX_FROM_BIT(nframes); i++){
    if (frames[i] != 0xFFFFFFFF){
			for (j = 0; j < 32; j++){
				if (!(frames[i]&(0x1 << j))) return i*4*8+j;
      }
    }
  }
}

// allocate 1 (one) frame
void alloc_f(page_t* page, int is_k, int is_write){
	if(page->frame != 0) return;
	else {
		uint32_t idx = first_frame();
		if(idx == (uint32_t)-1) printf("Paging --> No free frames..\n");
		set_frame(idx*0x1000); // Take control of the frame
		page->present = 1; // It exists...
		page->rw			= (is_write) ? 1 : 0; // should write to it?
		page->user		= (is_k)		 ? 0 : 1; // user mode?
		page->frame		= idx;
	}
}

// dealloc frame
void dealloc_f(page_t* page){
	uint32_t frame;
	if(!(frame = page->frame)) return; // page does not have a alloc. frame
	clear_frame(frame);
	page->frame = 0x00; // No frame!
}




void page_fault(registers_t regs){
	uint32_t fault_addr; // stored in CR2 register
	// get CR2 and store in fault_addr
	asm("mov %%cr2, %0" : "=r"(fault_addr));

	// error code gives details of what happens
	int present  = !(regs.err_code & 0x1);
	int rw			 = regs.err_code & 0x2;
	int us			 = regs.err_code & 0x4;
	int reserved = regs.err_code & 0x8;
	int id			 = regs.err_code & 0x10;

	printf("Page Fault occurred.\n\n");
	printf("Order: Present, RW, US, Reserved\n");
	printf("%d | %d | %d | %d\n\n", present, rw, us, reserved);
	printf("Fault Addr --> %x\n", fault_addr);
}


void initialize_paging(){
	// size of physical memory
	uint32_t mm_end = 0x1000000; // assume 16MB

	nframes = mm_end / 0x1000;
	frames = (uint32_t*)kmalloc(INDEX_FROM_BIT(nframes));
	memset(frames, 0, INDEX_FROM_BIT(nframes));

	// create page directory
	kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
	memset(kernel_directory, 0, sizeof(page_directory_t));
	current_directory = kernel_directory;

	// identity map (phys addr -> virtual addr)
	int i = 0;
	while(i < placement_address){
		// readable but not writeable from UMODE
		alloc_f(get_page(i, 1, kernel_directory), 0, 0);
		i += 0x1000;
	}

	// If a page fault occurs, go to page fault handler.
	register_interrupt_handler(14, page_fault);

	// finally, enable paging
	switch_page_directory(kernel_directory);
}

void switch_page_directory(page_directory_t* dir){
	current_directory = dir;
	asm volatile("mov %0, %%cr3":: "r"(&dir->phys_tables));
	uint32_t cr0;
	asm volatile("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000; // Enable paging!
	asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page_t* get_page(uint32_t address, int make, page_directory_t *dir){
	address /= 0x1000; // addres into index
	uint32_t table_idx = address / 1024; // find page table containing addr.
	if(dir->tables[table_idx]) return &dir->tables[table_idx]->pages[address%1024];
	else if(make){
		uint32_t tmp;
		dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
		memset(dir->tables[table_idx], 0, 0x1000);
		dir->phys_tables[table_idx] = tmp | 0x7;
		return &dir->tables[table_idx]->pages[address%1024];
	}
	// no case
	return 0;
}