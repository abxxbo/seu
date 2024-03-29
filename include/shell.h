#pragma once

#include <libc/stdio.h>
#include <libc/stdint.h>
#include <libc/string.h>


// Seu will also look through the active directory and try and execute anything
// if the command is equal to a specific file


char* recognized_commands[] = {
	"help"
};

// This is just a brief summary on what each command does
// When 'help' is invoked, the output
// should look like:
//    [cmd]: [summary]
char* brief_summary[] = {
  "Displays all commands with a brief summary on what they do.", // help command
};

int reg_cmd_l = sizeof(recognized_commands)/sizeof(recognized_commands[0]);

int ask_shell_cmd(char* buffer){
	for(int i = 0; i < reg_cmd_l; i++){
		if(strstr(buffer, recognized_commands[i]) != 127){
     
      // help command
			if(strstr(buffer, recognized_commands[0]) == 0){
				// unoptimized as hell, but eh, runs quick enough
				for(int j = 0; j < reg_cmd_l; j++){
					printf("%s: %s\n", recognized_commands[j], brief_summary[j]);
				}
				return 0;
			}
		} else {
			if(strcmp(buffer, "") == 0) return 0;
		}
	}
	return 1;
}