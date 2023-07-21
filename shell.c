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

	return input;
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
        char *token;

	char **args = (char **)malloc(MAX_ARGS * sizeof(char *));
	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, DELIMITER);
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, DELIMITER);
	}
	args[i] = NULL;

	return args;
}

/**
 * execute_command - Executes the command specified by the user.
 *
 * @args: The arguments array containing the command and its arguments.
 */
void execute_command(char **args)
{
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		wait(NULL);
	}
}

int main(void)
{
	char *input;
	char **args;

	while (1)
	{
		display_prompt();
		input = read_input();
		args = parse_input(input);

		/* Check if the user entered any input */
		if (args[0] != NULL)
		{
			execute_command(args);
		}

		/* Free allocated memory */
		free(input);
		free(args);
	}

	return 0;
}
