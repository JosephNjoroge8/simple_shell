#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_INPUT 100
#define MAX_ARGS 64
void handle_arguments(int argc, char *argv[]);
int main();
char *retrieve_path();
void tokenize_path(char *path, char *paths[]);
char *find_executable(char *command, char *paths[]);
int shell_exit(char **args);
int shell_env(char **args);
extern char **environ;
void handle_command(char *input, char *paths[], char *argv[]);
void execute_command(char *pargs[], char *paths[], char *argv[]);

#define MAX_PATH 2050
#define MAX_PATH_LEN 1024
#endif     
