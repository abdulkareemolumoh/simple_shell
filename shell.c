#include "shell.h"

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
	printf("($) ");
}

/**
 * read_input - Reads user input from the command line.
 *
 * Return: A pointer to the input string.
 */
char *read_input(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t chars_read = getline(&input, &input_size, stdin);

	if (chars_read == -1)
	{
		if (feof(stdin))
		{
			/* End of file (Ctrl+D) */
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
	}

	return (input);
}

/**
 * parse_input - Tokenizes the input string into separate arguments.
 *
 * @input: The input string to be parsed.
 *
 * Return: A double pointer to an array of strings (arguments).
 */
char **parse_input(char *input)
{
	int i = 0;
	char **args = (char **)malloc(MAX_ARGS * sizeof(char *));
	char *start = input;

	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	while (*input && i < MAX_ARGS - 1)
	{
		while (isspace(*input))
			input++;

		if (*input == '\0')
			break;

		while (*input && !isspace(*input))
			input++;

		if (*input)
			*input++ = '\0';

		args[i++] = strdup(start);

		if (args[i - 1] == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}
	args[i] = NULL;

	return (args);
}

/**
 * setenv_builtin - Set or modify an environment variable.
 *
 * @args: The arguments array containing the command and its arguments.
 *
 * Return: Always returns 0.
 */
int setenv_builtin(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (0);
	}

	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
		return (0);
	}

	return (0);
}

/**
 * unsetenv_builtin - Unset an environment variable.
 *
 * @args: The arguments array containing the command and its arguments.
 *
 * Return: Always returns 0.
 */
int unsetenv_builtin(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (0);
	}

	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
		return (0);
	}

	return (0);
}
