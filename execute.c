#include "main.h"
/**
 *execution_cmd - executing the command
 *@env: variables of the main function
 *@cmd_part: pointer command input
 *@limits: character in limiting
 *
 */
void execution_cmd(char **env, char *cmd_part, char *limits)
{
	int i = 0;
	char *cmd;
	struct stat *rt;
	char *arguments[100] = {" ", NULL};

	rt = malloc(sizeof(struct stat));
	cmd = strtok(cmd_part, limits);

	if (cmd != NULL)
	{
		if (strcmp(cmd, "setenv") == 0)
		{
			i = 0;
			arguments[0] = cmd;
		}
		else if (strcmp(cmd, "unsetenv") == 0)
		{
			i = 2;
			arguments[0] = cmd;
		}
		else
		{
			arguments[0] = path(cmd);
		}
		arguments[0] = path(cmd);
		while (arguments[i] != NULL)
		{
			i++;
			arguments[i] = strtok(NULL, limits);
		}
		if (strcmp(cmd, "setenv") == 0)
		{
			set_environment(arguments);
		}
		else if (strcmp(cmd, "unsetenv") == 0)
		{
			unset_environment(arguments);
		}
		else
		{
		checkpath(arguments, env, &rt, cmd_part);
		}
	}
	free(rt);
}
