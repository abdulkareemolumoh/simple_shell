#include "shell.h"

/**
 * main - Entry point for the shell program
 * @argc: arguments
 * @argv: arguments
 * Return: 0 on success, otherwise a non-zero value
 */
int main(int argc, char **argv)
{
	char *input;
	char **args;
	bool should_exit = false;
	handle_arguments(argc, argv);
	while (!should_exit)
	{
		display_prompt();
		input = read_input();
		args = parse_input(input);
		if (args[0] != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				should_exit = exit_builtin();
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
				handle_non_builtin_command(args);
			}
		}
		free(input);
		free(args);
	}
	return (0);
}

/**
 * handle_command - Entry point for the shell program
 * @args: arguments
 * Return: 0 on success, otherwise a non-zero value
 */
void handle_command(char **args)
{
	/* Function to execute a non-builtin command */
	execute_command(args);
}

/**
 * handle_builtins - Entry point for the shell program
 * @args: arguments
 * Return: 0 on success, otherwise a non-zero value
 */
void handle_builtins(char **args)
{
	/* Function to handle the built-in commands */
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
		/* Handle the cd built-in command */
	}
	/* Add more built-in commands here if needed */
}

/**
 * handle_cd_builtin - Entry point for the shell program
 * @args: arguments
 * Return: 0 on success, otherwise a non-zero value
 */
void handle_cd_builtin(char **args)
{
	char cwd[MAX_COMMAND_LENGTH];
	/* Handle the cd built-in command */
	/* If no argument provided, change to home directory */
	if (args[1] == NULL)
	{
		chdir(getenv("HOME"));
	}
	else if (strcmp(args[1], "-") == 0)
	{
		/* Handle cd - */
		char *old_pwd = getenv("OLDPWD");

		if (old_pwd != NULL)
			chdir(old_pwd);
	}
	else
	{
		chdir(args[1]);
	}
	/* Update the PWD environment variable */

	getcwd(cwd, sizeof(cwd));
	setenv("PWD", cwd, 1);
}

/**
 * handle_non_builtin_command - Entry point for the shell program
 * @args: arguments
 * Return: 0 on success, otherwise a non-zero value
 */
void handle_non_builtin_command(char **args)
{
	/* Function to execute a non-builtin command */
	execute_command(args);
}

