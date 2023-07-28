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
	int i;

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
	for (i = 0; paths[i] != NULL; i++)
	{
		free(paths[i]);
	}
	if (path != NULL)
	{
	free(path);
	}

        return (0);
}
/**
 *handle_command - handle some commands
 *@input: input of the commands
 *@paths: paths of the files
 *@argv: argument vector
 */
void handle_command(char *input, char *paths[], char *argv[])
{
        char *pargs[MAX_ARGS];


                pargs[0] = strdup(input);
		if (pargs[0] == NULL)
		{
			perror("Error");
			return;
		}
                pargs[1] = NULL;

                if (strcmp(pargs[0], "exit") == 0)
                {
                        free(pargs[0]);
                        exit(EXIT_SUCCESS);
                }
                else if (strcmp(pargs[0], "env") == 0)
                {
                        shell_env(pargs);
                }
                else
                {
                        execute_command(pargs, paths, argv);
                }
                free(pargs[0]);
}
/**
 *execute_command - execute some commands using the execve
 *@pargs: pargs
 *@paths: path of the files
 *@argv: argument vector
 */
void execute_command(char *pargs[], char *paths[], char *argv[])
{
                char *executable_path;
                pid_t pid;
                int status;
                char *env[] = {NULL};

                executable_path = find_executable(pargs[0], paths);
                if (executable_path == NULL)
                {
                        fprintf(stderr, "%s: %d: %s: not found\n", argv[0], 1, pargs[0]);
                        return;
                }
                pid = fork();
                if (pid == -1)
                {
                        perror("Error");
                        exit(EXIT_FAILURE);
                }
                else if (pid == 0)
                {
                        if (execve(pargs[0], pargs, env) == -1)
                        {
                                free(executable_path);
                                perror("error");
                                exit(EXIT_FAILURE);
                        }
                }
                else
                {
                        waitpid(pid, &status, 0);
                }
                free(executable_path);
}

