#include "shell.h"

/**
 * handle_arguments - Entry point for the shell program
 * @argc: arguments
 * @argv: arguments
 * Return: 0 on success, otherwise a non-zero value
 */
void handle_arguments(int argc, char **argv)
{
	char line[MAX_COMMAND_LENGTH];

	if (argc > 1)
	{
		FILE *file = fopen(argv[1], "r");

		if (file == NULL)
		{
			perror("fopen");
			exit(EXIT_FAILURE);
		}

		while (fgets(line, sizeof(line), file))
		{
			line[strcspn(line, "\n")] = 0;
			handle_input_line(line);
		}

		fclose(file);
		exit(EXIT_SUCCESS);
	}
}

/**
 * handle_input_line - Processes a single line of input from the file
 * @line: Input line to process
 */
void handle_input_line(char *line)
{
	char *input = strdup(line);
	char **args = parse_input(input);

	if (args[0] != NULL)
	{
		if (strcmp(args[0], "exit") == 0)
		{
			exit_builtin();
		}
		else if (strcmp(args[0], "env") == 0)
		{
			env_builtin();
		}
		else if (strcmp(args[0], "setenv") == 0)
		{
			setenv_builtin(args);
		}
		else if (strcmp(args[0], "unsetenv") == 0)
		{
			unsetenv_builtin(args);
		}
		else if (strcmp(args[0], "cd") == 0)
		{
			handle_cd_builtin(args);
		}
		else
		{
			execute_command(args);
		}
	}

	free(input);
	free(args);
}
