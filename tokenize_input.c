#include "main.h"

/**
 * tokenize_input - Tokenizes the input string into arguments
 * @input: The input string to tokenize
 * @args: An array to store the arguments
 * @arg_count: A pointer to store the argument count
 *
 * Return: void
 */
void tokenize_input(char *input, char **args, int *arg_count)
{
	char *token;

	*arg_count = 0;
	token = strtok(input, " ");

	while (token != NULL)
	{
		args[*arg_count] = token;
		(*arg_count)++;
		token = strtok(NULL, " ");
	}

	args[*arg_count] = NULL; /* Terminate the args array with NULL */
}
