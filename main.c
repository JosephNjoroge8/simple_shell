#include "main.h"
/**
 *
 *
 *
 */
void execute_command(char *command)
{
        pid_t pid;

        pid = fork();
        if (pid < 0)
        {
                perror("error");
                exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
		char *argv[2];
		argv[0] = command;
		argv[1] = NULL;

                execve(command, argv, NULL);
                perror("error");
                exit(EXIT_FAILURE);
        }
        else
        {
                wait(NULL);
        }
}
/**
 *
 *
 *
 *
 *
 *
 */
char *write_input()
{
	size_t len;
	char *input = malloc(MAX_INPUT);

	if (!input)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	printf("$ ");
	fflush(stdout);

	if(fgets(input, MAX_INPUT, stdin) == NULL)
	{
		free(input);
		return (NULL);
	}
	len = strlen(input);
	if (input[len - 1] == '\n')
	{
		input[len - 1] = '\0';
	}
	return (input);
}
/**
 *
 *
 *
 *
 *
 */
int main(void)
{
	char *input;

	while(1)
	{
		input = write_input();
		if (input == NULL)
		{
			printf("\n");
			break;
		}
		if (input[0] != '\0')
		{
			execute_command(input);
		}
		free(input);
	}
	return (0);
}
