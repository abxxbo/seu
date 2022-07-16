#pragma once

#include <stdint.h>
#include <stddef.h>

#include <libc/stdio.h>
#include <libc/string.h>

char* recognized_commands[] = {
	"help"			// ... only a help command, just print out each entry here.
};

int ask_shell_cmd(char* buffer){
	// We should not be able to reach here, since we execute the commands,
	// so return 1
	return 1;
}