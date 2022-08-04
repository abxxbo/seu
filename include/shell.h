#pragma once

#include <libc/stdio.h>
#include <libc/stdint.h>
#include <libc/string.h>


// Seu will also look through the active directory and try and execute anything
// if the command is equal to a specific file


char* recognized_commands[] = {
	"help",			// ... only a help command, just print out each entry here.
  "echo"
};

int reg_cmd_l = sizeof(recognized_commands)/sizeof(recognized_commands[0]);

int ask_shell_cmd(char* buffer){
	for(int i = 0; i < reg_cmd_l; i++){ // hardcoded value for length of recg_cmd, change.
		if(strstr(buffer, recognized_commands[i]) != 127){
     
      // help command
			if(strstr(buffer, recognized_commands[0]) == 0){
				printf("Available commands:\n");
				// unoptimized as hell, but eh, runs quick enough
				for(int j = 0; j < reg_cmd_l; j++){
					printf("%s\n", recognized_commands[j]);
				}
				return 0;
			}

      // echo command
      if(strstr(buffer, recognized_commands[1]) == 0){
        for(int i = 5; i < strlen(buffer); i++){
          char c = buffer[i];
          if(c == '\n') puts("\n");
          else putc(c);
        }
        puts("\n");
        return 0;
      }
		} else {
			if(strcmp(buffer, "") == 0) return 0;
		}
	}
	return 1;
}