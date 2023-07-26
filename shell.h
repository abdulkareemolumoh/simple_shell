#ifndef MYSHELL_H
#define MYSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64
#define DELIMITER " \t\r\n\a"
#define BUFFER_SIZE 1024

extern char **environ;

void display_prompt(void);
char *read_input(void);
char **parse_input(char *input);
void execute_command(char **args);
int search_command_in_path(char **args, char *path);
void execute_command(char **args);
int env_builtin(void);
char *my_getline(void);
bool exit_builtin(void);
int execute_with_path(char *full_path, char **args);
int setenv_builtin(char **args);
int unsetenv_builtin(char **args);
void handle_arguments(int argc, char **argv);
void handle_command(char **args);
void handle_builtins(char **args);
void handle_cd_builtin(char **args);
void handle_non_builtin_command(char **args);
void handle_input_line(char *line);

#endif /* MYSHELL_H */

