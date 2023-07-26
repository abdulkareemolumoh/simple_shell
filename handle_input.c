#include "main.h"

/**
 * handle_input - Handles the user's input
 * @input: A string representing the user's input
 *
 * Return: void
 */

void handle_input(char *input)
{
	char *args[MAX_ARGS];
	int arg_count = 0;

	/* Check for exit command */
	if (strcmp(input, "exit") == 0)
	{
		exit_shell();
		return;
	}

	/* Check for env command */
	if (strcmp(input, "env") == 0)
	{
		print_environment();
		return;
	}

	tokenize_input(input, args, &arg_count);
	execute_command(args);
}


