#include <libc/stdio.h>

#include <stddef.h>
#include <stdint.h>

extern uint32_t end;
uint32_t placement_address = (uint32_t)&end;

uint32_t kmalloc_int(uint32_t sz, int align, uint32_t *phys){
    if (align == 1 && (placement_address & 0xFFFFF000) ){
        // Align the placement address;
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    } else {
        return 1;
    }
    if (phys) *phys = placement_address;
    else return 1;
    uint32_t tmp = placement_address;
    placement_address += sz;
    return tmp;
}

uint32_t kmalloc_a(uint32_t sz){
    return kmalloc_int(sz, 1, 0);
}

uint32_t kmalloc_p(uint32_t sz, uint32_t *phys){
    return kmalloc_int(sz, 0, phys);
}

uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys){
    return kmalloc_int(sz, 1, phys);
}

uint32_t kmalloc(uint32_t sz){
    return kmalloc_int(sz, 0, 0);
}