#include "main.h"

/**
 * print_environment - Prints the current environment.
 */

void print_environment(void)
{
	char **environ = __environ;
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

