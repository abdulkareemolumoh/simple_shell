#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_ARGS 64

/* Function prototypes */
void execute_shell(void);
char *get_input(void);
void handle_input(char *input);
void tokenize_input(char *input, char **args, int *arg_count);
void execute_command(char **args);
void exit_shell(void);
void print_environment(void);

#endif /* MAIN_H */


