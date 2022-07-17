#pragma once


// convert an integer to a string with said base.
// example:
//	itos(0xc0ff33, 16) returns "c0ff33" 
char* itos(unsigned int num, int base){ 
	char rep[]= "0123456789ABCDEF";
	char buf[50]; 
	char *ptr; 

	ptr = &buf[49]; 
	*ptr = '\0'; 

	do { 
		*--ptr = rep[num%base];
		num /= base;
	} while(num != 0);

	return ptr;
}


void* memset (void *dest, int val, unsigned int len){
  unsigned char *ptr = dest;
  while (len-- > 0) *ptr++ = val;
  return dest;
}