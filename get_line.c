#include "main.h"

/**
 * get_line - Reads input from the user.
 *
 * Return: A string representing the user's input.
 */
char *get_line(void)
{
	static char line[256]; /* Static buffer to store the input line*/
	static int line_len;
	int c;

	while (true)
	{
		c = getchar();

		if (c == EOF)
		{
			if (line_len == 0) /* End of file and no characters read, exit the shell*/
				exit_shell();

			line[line_len] = '\0';
			break;
		}
		else if (c == '\n') /* End of line, return the input*/
		{
			line[line_len] = '\0';
			break;
		}

		/* Store the character in the buffer*/
		line[line_len] = c;
		line_len++;

		if (line_len == 255)
		{
			line[line_len] = '\0';
			break;
		}
	}

	line_len = 0; /* Reset line_len for the next input */
	return (line);
}

