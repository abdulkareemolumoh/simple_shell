#include "shell.h"

/**
 * env_builtin - Prints the current environment.
 *
 * Return: Always returns 0.
 */
int env_builtin(void)
{
	char **env_ptr = environ;

	while (*env_ptr != NULL)
	{
		printf("%s\n", *env_ptr);
		env_ptr++;
	}

	return (0);
}

/**
 * read_input_to_buffer - Reads input from stdin into the buffer.
 *
 * @buffer: The buffer to store the input characters.
 * @buffer_pos: The current position in the buffer.
 * @chars_in_buffer: The number of characters in the buffer.
 *
 * Return: The number of characters read, or -1 if an error occurs or
 * EOF is reached.
 */
int read_input_to_buffer(char *buffer, int *buffer_pos,
		int *chars_in_buffer)
{
	*buffer_pos = 0;
	*chars_in_buffer = read(STDIN_FILENO, buffer, BUFFER_SIZE);
	return (*chars_in_buffer);
}

/**
 * read_line_from_buffer - Reads a line from the buffer.
 *
 * @buffer: The buffer containing the input characters.
 * @buffer_pos: The current position in the buffer.
 * @chars_in_buffer: The number of characters in the buffer.
 *
 * Return: A pointer to the input line, or NULL if an error occurs or
 * EOF is reached.
 */
char *read_line_from_buffer(char *buffer, int *buffer_pos,
		int *chars_in_buffer)
{
	char *input = NULL;
	int input_pos = 0;

	while (*buffer_pos < *chars_in_buffer)
	{
		if (buffer[*buffer_pos] == '\n')
		{
			input = (char *)realloc(input, (input_pos + 1) * sizeof(char));
			input[input_pos] = '\0';
			(*buffer_pos)++;
			return (input);
		}

		input = (char *)realloc(input, (input_pos + 1) * sizeof(char));
		input[input_pos++] = buffer[(*buffer_pos)++];
	}

	return (NULL);
}

/**
 * my_getline - Reads a line from stdin using a buffer and reduces the number
 * of read system calls.
 *
 * Return: A pointer to the input line, or NULL if an error occurs
 * or EOF is reached.
 */
char *my_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int buffer_pos;
	static int chars_in_buffer;

	char *input = NULL;
	int input_pos = 0;

	while (1)
	{
		if (buffer_pos >= chars_in_buffer)
		{
			chars_in_buffer = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			buffer_pos = 0;

			if (chars_in_buffer <= 0)
				break;
		}

		if (buffer[buffer_pos] == '\n')
		{
			input = (char *)realloc(input, (input_pos + 1) * sizeof(char));
			input[input_pos] = '\0';
			buffer_pos++;
			break;
		}

		input = (char *)realloc(input, (input_pos + 1) * sizeof(char));
		input[input_pos++] = buffer[buffer_pos++];
	}

	return (input);
}
