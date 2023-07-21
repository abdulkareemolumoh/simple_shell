#ifndef MYSHELL_H
#define MYSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64
#define DELIMITER " \t\r\n\a"

void display_prompt(void);
char *read_input(void);
char **parse_input(char *input);
void execute_command(char **args);

#endif /* MYSHELL_H */

