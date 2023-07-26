#include "main.h"

/**
 * get_input - Reads input from the user
 *
 * Return: A string representing the user's input
 */
char *get_input(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t linelen;

	linelen = getline(&line, &bufsize, stdin);
	if (linelen == -1)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}

	if (line[linelen - 1] == '\n')
	{
		line[linelen - 1] = '\0';
	}

	if (line[0] == '\0')
	{
		free(line);
		return (get_input());
	}

	return (line);
}

