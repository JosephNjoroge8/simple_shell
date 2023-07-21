#include <stdio.h>
#include <stdlib.h>

/*
 * custom_getline - gets a new line for the user
 * @lineptr: pointer to a buffer to store the line
 * @n: pointer to the size of the buffer
 * @stream: file stream to read from
 *
 * Return: number of characters read or -1 if error orEOF
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	if (lineptr == NULL || n == NULL)
	{
		size_t initial_size = 128;
		*lineptr = (char *)malloc(initial_size * sizeof(char));
		if (*lineptr == NULL)
		{
			perror("Sorry, Memory allocation failed");
			return (-1);
		}
		*n = initial_size;
	}
	size_t count = 0;
	int current_char;

	while ((current_char = fgetc(stream)) != EOF && current_char != '\n')
	{
		if (count >= *n - 1)
		{
			size_t new_size = *n * 2;
			char *new_ptr = (char *)realloc(*lineptr, new_size);
			if (new_ptr == NULL)
			{
				perror("Sorry, Memory allocation failed");
				free(*lineptr);
				*lineptr = NULL;
				return (-1);
			}
			*lineptr = new_ptr;
			*n = new_size;
		}
		(*lineptr)[count] = current_char;
		count++;
	}
	if (count == 0)
	{
		return (-1);
	}
	(*lineptr)[count] = '\0';
	return (count);
}
/**
 * main - entry point of the program
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;

	printf("$");
	ssize_t read_chars = custom_getline(&line, &len, stdin);
	if (read_chars != -1)
	{
		printf("%s", line);
	}
	free(line);
	return (0);
}