#include "main.h"

void execute_shell(void);
char *get_input(void);
void handle_input(char *input);
void tokenize_input(char *input, char **args, int *arg_count);
void execute_command(char **args);

/**
 * main - Entry point for the shell program
 *
 * Return: 0 on success, otherwise a non-zero value
 */
int main(void)
{
	execute_shell();
	return (0);
}

/**
 * execute_shell - The main loop that executes the shell program
 *
 * Return: void
 */
void execute_shell(void)
{
	char *input;

	while (1)
	{
		printf("$ ");
		input = get_input();
		handle_input(input);
		free(input);
	}
}

