#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_TOKENS 64
#define DELIMITERS " \t\r\n\a"
void display_prompt();
char **parse_input(char *input);
void execute_command(char **tokens);
int main(int argc, char *argv[]);
#endif
