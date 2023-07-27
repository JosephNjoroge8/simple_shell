#include "main.h"
/*
 *
 *
 */
void display_prompt() 
{
    printf("($) ");
    fflush(stdout);
}
char **parse_input(char *input) 
{
	int i = 0;
	char *token;

    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    if (!tokens) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, DELIMITERS);
    while (token) {
        tokens[i++] = token;
        token = strtok(NULL, DELIMITERS);
    }
    tokens[i] = NULL;

    return tokens;
}

void execute_command(char **tokens)
{
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execvp(tokens[0], tokens) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

int main(int argc, char *argv[]) 
{
	char **tokens;

    char input[MAX_COMMAND_LENGTH];

    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    while (1) {
        display_prompt();
        if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL) {
            printf("\n");
            break;
        }

        tokens = parse_input(input);
        if (tokens[0] != NULL) {
            if (strcmp(tokens[0], "exit") == 0) {
                break;
            }
            execute_command(tokens);
        }
        free(tokens);
    }

    return 0;
}
