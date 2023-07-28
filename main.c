#include "main.h"
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
	dest[dest_len + i] = '\0';
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
void checkpath(char **arguments, char **env, struct stat **rt, char *cmd_line)
{
	pid_t pid;
	int status;

	if (stat(arguments[0], *rt) == 0)
	{
		pid = fork();
		switch (pid)
		{
			case -1:
				free(*rt);
				exit(EXIT_FAILURE);
			case 0:
				if (execve(arguments[0], arguments, env) == -1)
				{
					free(*rt);
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
					free(*rt);
					exit(errno);
				}
		}
	}
	else
	{
		cusstimation_error(arguments[0]);
		if (!isatty(STDIN_FILENO))
		{
			exit(127);
		}
	}
}
/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument void
 * @env: Environmental variable
 * Return: Always 0
 */
int main(int argc __attribute__((unused)),
char *argv[] __attribute__((unused)),
char **env)
{
	size_t x = 0;
	char *s_line = NULL;

	while (1)
	{
		shell_start();

		if (getline(&s_line, &x, stdin) == -1)
		{
			exit(EXIT_SUCCESS);
		}

		if (_strcmp(s_line, "exit\n") == 0)
		{
			free(s_line);
			exit(0);
		}

		execution_cmd(env, s_line, " \n\t\v\b\r\f");
		free(s_line);
	}
	return (0);
}
