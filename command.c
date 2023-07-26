#include "main.h"
/**
 *shell_exit - exits it is a built in command
 *@args: arguments
 *Return: 0 success
 */
int shell_exit(char **args)
{
	(void)args;

	exit(EXIT_SUCCESS);
}
/**
 *shell_env - shell enviroment
 *@args: arguments
 *Return: 0 success
 */
int shell_env(char **args)
{
	char **env = environ;
	(void)args;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (1);
}

