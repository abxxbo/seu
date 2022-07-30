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


int strlen(char* s){
	int ct;
	for(; *s != '\0'; *s++) ct++;
	return ct;
}

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

void* memset (void *dest, int val, unsigned int len){
  unsigned char *ptr = dest;
  while (len-- > 0) *ptr++ = val;
  return dest;
}


char* strcpy(char* source, char* dest){
	while(*source != '\0') *dest++ = *source++;
	return dest;
}


int strcmp(const char *l, const char *r){
	for (; *l==*r && *l; l++, r++);
	return *(unsigned char *)l - *(unsigned char *)r;
}
