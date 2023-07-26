#include "main.h"

/**
 * execute_command - Executes a command with arguments
 * @args: The command and its arguments as an array of strings
 *
 * Return: void
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		/* Error */
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
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
			exit(EXIT_FAILURE);
		}
	}
}

