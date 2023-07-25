#include "shell.h"

/**
 * main - Entry point for the shell program
 *
 * Return: 0 on success, otherwise a non-zero value
 */
int main(void)
{
	char *input;
	char **args;
	bool should_exit = false;

	while (!should_exit)
	{
		display_prompt();
		input = my_getline();
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
			else
			{
				execute_command(args);
			}
		}

		free(input);
		free(args);
	}

	return (0);
}

/**
 * execute_with_path - Executes the command with the specified full path
 * in a child process.
 *
 * @full_path: The full path to the executable.
 * @args: The arguments array containing the command and its arguments.
 *
 * Return: 0 on success, -1 otherwise.
 */
int execute_with_path(char *full_path, char **args)
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
		execv(full_path, args);
		perror("execv");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		int status;

		wait(&status);
		return (WIFEXITED(status) && WEXITSTATUS(status) == 0);
	}
}

/**
 * search_command_in_path - Search for the command in the directories
 * listed in the PATH.
 *
 * @args: The arguments array containing the command and its arguments.
 * @path: The PATH environment variable value.
 *
 * Return: 1 if the command was not found, 0 otherwise.
 */
int search_command_in_path(char **args, char *path)
{
	char *path_copy = strdup(path);
	char *dir;
	int found = 0;

	if (path_copy == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}

	dir = strtok(path_copy, ":");

	while (dir != NULL && !found)
	{
		/* Construct the full path to the executable */
		char *full_path = (char *)malloc(strlen(dir) + strlen(args[0]) + 2);

		if (full_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		sprintf(full_path, "%s/%s", dir, args[0]);

		found = execute_with_path(full_path, args);

		/* Cleanup */
		free(full_path);

		/* Move on to the next directory in PATH */
		dir = strtok(NULL, ":");
	}

	/* If the loop completes, the command was not found in PATH */
	return (!found);
}

/**
 * execute_command - Executes the command specified by the user.
 *
 * @args: The arguments array containing the command and its arguments.
 */
void execute_command(char **args)
{
	if (access(args[0], F_OK) == 0 ||
			search_command_in_path(args, getenv("PATH")) == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		exit(EXIT_FAILURE);
	}
}

/**
 * exit_builtin - Exits the shell.
 *
 * Return: Always returns 1 to indicate the shell should exit.
 */
bool exit_builtin(void)
{
	exit(EXIT_SUCCESS);
	return (true);
}
