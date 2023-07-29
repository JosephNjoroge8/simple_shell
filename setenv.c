#include "main.h"
/**
 * set_environment - Sets a new environment variable or modifies an existing one
 * @arguments: Parameters
 */
void set_environment(char **arguments)
{
	if (arguments[1] != NULL && arguments[2] != NULL)
	{
		if (setenv(arguments[1], arguments[2], 1) == -1)
		{
			perror("Error setting environment variable");
		}
	}
	else
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
	}
}

/**
 * unset_environment - Unsets/removes an environment variable
 * @arguments: Parameters
 */
void unset_environment(char **arguments)
{
	if (arguments[1] != NULL)
	{
		if (unsetenv(arguments[1]) == -1)
		{
			perror("Error unsetting environment variable");
		}
	}
	else
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
	}
}
