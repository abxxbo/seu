#pragma once

#include <libc/stdio.h>

// assume some things
#define WIDTH  80
#define HEIGHT 25
#define KERN_V "prerelease" // idk

void sfetch_run(){
	printf(" __     OS: Seu OS\n");
	printf("/       Resolution:\n");
	printf("\\__        W: %d\n", WIDTH);
	printf("   \\       H: %d\n", HEIGHT);
	printf("___/    KERN_V: %s\n", KERN_V);
}