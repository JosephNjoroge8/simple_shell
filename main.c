#include "main.h"
/**
 *main - entery point
 *@argc: argument count
 *@argv: argument vector
 *Return: 0 sucess
 *
 *
 */
int main(int argc __attribute__((unused)), char *argv[])
{
	char input[MAX_INPUT];
	char *paths[MAX_PATH];
	char *path;

	path = retrieve_path();
	tokenize_path(path, paths);
	while (1)
	{
		printf("$ ");
		fflush(stdout);
		if (fgets(input, MAX_INPUT, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		if (input[0] == '\0')
		{
			continue;
		}
		handle_command(input, paths, argv);
	}
	return (0);
}
/**
 *handle_command - handle some commands
 *@input: input of the commands
 *@paths: paths of the files
 *@argv: argument vector
 */
void handle_command(char *input, char *paths[], char *argv[] __attribute__((unused)))
{
	char *pargs[MAX_ARGS];
	char *executable;
	int i = 0;

	tokenize_path(input, pargs);

	if (strcmp(pargs[0], "exit") == 0)
	{
		shell_exit(pargs);
		return;
	}
	else if (strcmp(pargs[0], "env") == 0)
	{
		shell_env(pargs);
		return;
	}
	executable = find_executable(pargs[0], paths);
	if (executable != NULL)
	{
		execute_command(pargs, paths);
		free(executable);
	}
	else
	{
		printf("%s:command not found\n", pargs[0]);
	}
	for (i = 0; pargs[i] != NULL; i++)
	{
		free(pargs[i]);
	}
}
/**
 *execute_command - execute some commands using the execve
 *@pargs: pargs
 *@paths: path of the files
 *@argv: argument vector
 */
void execute_command(char *pargs[], char *paths[])
{
	pid_t child_pid;
	int status;
	char *executable;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		executable = find_executable(pargs[0], paths);
		execv(executable, pargs);
		perror("execv");
		free(executable);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}


