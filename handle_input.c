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
	int i;

	bool in_word = false;

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

	/* Tokenize the input including arguments*/
	for (i = 0; input[i]; i++)
	{
		if (isspace(input[i]))
		{
			input[i] = '\0';
			in_word = false;
		}
		else
		{
			if (!in_word)
			{
				args[arg_count++] = &input[i];
				in_word = true;
			}
		}
	}
	args[arg_count] = NULL; /* Terminate the args array with NULL*/

	execute_command(args);
}
