#pragma once

#include <stddef.h>
#include <stdint.h>

char* itos(unsigned int num, int base){ 
	static char repr[]= "0123456789ABCDEF";
	static char buffer[50]; 
	char *ptr; 

	ptr = &buffer[49]; 
	*ptr = '\0'; 

	do {
		*--ptr = repr[num%base]; 
		num /= base; 
	}while(num != 0); 

	return(ptr); 
}

void* memset(void *dest, int val, size_t len){
  unsigned char *ptr = dest;
  while (len-- > 0)
    *ptr++ = val;
  return dest;
}

int strcmp(const char *p1, const char *p2){
  const unsigned char *s1 = (const unsigned char *) p1;
  const unsigned char *s2 = (const unsigned char *) p2;
  unsigned char c1, c2;
  do {
		c1 = (unsigned char) *s1++;
		c2 = (unsigned char) *s2++;
	  if (c1 == '\0') return c1 - c2;
  } while (c1 == c2);
  return c1 - c2;
}

// Get length of string.
int strlen(char* f){
	int d;
	for(d = 0; *f != 0; *f++) d++;
	return d;
}

// Find SS in S. Return 0 if found, 127 if not
int strstr(char*s, char* ss){
	int len_ss = strlen(ss);
	int cont = 0;
	for(; *s != 0; *s++){
		if(*s == *ss) cont++;
		*ss++;
	}
	if(cont == len_ss) return 0;
	return 127;
}

char* strcpy(char* source, char* dest){
	while(*source != '\0') *dest++ = *source++;
	return dest;
}