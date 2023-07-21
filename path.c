#include "main.h"
/**
 *retrieve_path - retrieves the path of the environment
 *Return: the the path using the getenv
 *
 */
char *retrieve_path()
{
	char *path = getenv("PATH");
	char *copy = strdup(path);
	char *dire;
	char *result;
	int i = 0;

	result = malloc(sizeof(char) * MAX_PATH);
	if (result == NULL)
	{
		return (NULL);
	}
	dire = strtok(copy, ":");
	while (dire != NULL)
	{
		strcpy(result + i, dire);
		i += strlen(dire);
		result[i] = '/';
		i++;
		dire = strtok(NULL, ":");
	}
	result[i - 1] = '\0';

	return (result);
}
/**
 *tokenize_path-tokenize of the path
 *@path: path of the command
 *@paths:store the path of the command
 *Return: path
 */
void tokenize_path(char *path, char *paths[])
{
	int i = 0;

	paths[i] = strtok(path, ":");
	while (paths[i] != NULL && i < MAX_PATH - 1)
	{
		i++;
		paths[i] = strtok(NULL, ":");
	}
}
/**
 *find_executable-to check for the executable file
 *@cmd: represents the command entered
 *@paths:path of the command
 *Return: the copy of the executable file
 */
char *find_executable(char *cmd, char *paths[])
{
	int i;

	char full_path[MAX_PATH_LEN];

	if (access(cmd, X_OK) == 0)
	{
		return (strdup(cmd));
	}

	for (i = 0; paths[i] != NULL; i++)
	{
		sprintf(full_path, "%s/%s", paths[i], cmd);

		if (access(full_path, X_OK) == 0)
		{
			return (strdup(full_path));
					}
					}
					return (NULL);

}
