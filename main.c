#include "main.h"
/**
 * display_prompt - Displays shell prompt if input is coming
 * from the terminal
 * Return: Nothing
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO) != 0)
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * _strcmp - Compares the similarity of two input strings
 * @str1: String 1
 * @str2: String 2
 * Return: 0 (on success)
 */
int _strcmp(char *str1, char *str2)
{
	int index = 0;

	while (str1[index] != '\0' || str2[index] != '\0')
	{
		if (str1[index] != str2[index])
			return (str1[index] - str2[index]);

		index++;
	}
	return (0);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: Pointer to the concatenated string
 */
char *_strcat(char *dest, char *src)
{
	int dest_len = 0;
	int src_len = 0;
	int i = 0;

	while (dest[dest_len])
		dest_len++;

	while (src[src_len])
		src_len++;

	while (src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0'; /* Adding null terminator at the end */
	return (dest);
}

/**
 * path - Adds path prefix to the command
 * @cmd: Command to prefix with path
 * Return: the complete path
 */
char *path(char *cmd)
{
	char p1[50] = "/bin/";
	char p2[50] = "/usr/bin/";
	struct stat st;

	_strcat(p1, cmd);
	_strcat(p2, cmd);

	if (stat(p1, &st) == 0)
		return (strdup(p1));
	else if (stat(p2, &st) == 0)
		return (strdup(p2));

	return (strdup(cmd));
}

/**
 * checkpath - checks validity of a path
 * @arguments: parameters
 * @env: environment variables
 * @st: pointer to path info
 * @cmd_line: a pointer to line of args
 * Return: nothing
 */
void checkpath(char **arguments, char **env, struct stat **st, char *cmd_line)
{
	pid_t pid;
	int status;

	if (stat(arguments[0], *st) == 0)
	{
		pid = fork();
		switch (pid)
		{
			case -1:
				free(*st);
				exit(EXIT_FAILURE);
			case 0:
				if (execve(arguments[0], arguments, env) == -1)
				{
					free(*st);
					exit(EXIT_FAILURE);
				}
				break;
			default:
				wait(&status);
				free(arguments[0]);
				if (status != 0)
				{
					errno = 2;
					free(cmd_line);
					free(*st);
					exit(errno);
				}
		}
	}
	else
	{
		custom_error(arguments[0]);
		if (!isatty(STDIN_FILENO))
		{
			exit(127);
		}
	}
}

/**
 * custom_error - writes a custom error message to stderr
 * @cmd: erroneous command
 * Return: void
 */
void custom_error(char *cmd)
{
	static int errorCount;
	char *prefix = "./hsh: ";
	int cmdLen = 0;

	while (cmd[cmdLen])
		cmdLen++;

	errorCount++;
	write(STDERR_FILENO, prefix, 7);
	print_number(errorCount);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, cmdLen);
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * print_number - prints an int to stderr
 * @n: No to print out
 * Return: Nothing
 */
void print_number(int n)
{
	char num;

	if (n > 9)
	{
		print_number(n / 10);
	}

	num = (n % 10) + '0';
	write(2, &num, 1);
}

/**
 * execute_command - Executes the command and its arguments
 * @env: env variables of the main function
 * @cmd_line: Pointer to string containing commandline input
 * @delimiter: Delimiting character
 * Return: Nothing
 */
void execute_command(char **env, char *cmd_line, char *delimiter)
{
	int x = 0;
	char *command;
	struct stat *st = malloc(sizeof(struct stat));
	char *arguments[100] = {"", NULL};

	command = strtok(cmd_line, delimiter);

	if (command != NULL)
	{
		arguments[0] = path(command);
		while (arguments[x] != NULL)
		{
			x++;
			arguments[x] = strtok(NULL, delimiter);
		}

		checkpath(arguments, env, &st, cmd_line);
	}
	free(st);
}

/**
 * main - Entry point to the project
 * @argc: no of command line arguments (void)
 * @argv: Array of strings containing command-line args
 * @env: Environmental variable
 * Return: Always 0 (On success)
 */
int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)), char **env)
{
	size_t x = 0;
	char *s_line = NULL;

	while (1)
	{
		display_prompt();

		if (getline(&s_line, &x, stdin) == -1)
		{
			/* free(s_line); */
			exit(EXIT_SUCCESS);
		}

		if (_strcmp(s_line, "exit\n") == 0)
		{
			free(s_line);
			exit(0); /* Quit */
		}

		execute_command(env, s_line, " \n\t\v\b\r\f");
		free(s_line);
	}
	return (0);
}
