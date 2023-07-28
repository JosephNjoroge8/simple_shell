#ifndef MAIN_H
#define MAIN_H
int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)), char **env);
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100
#define MAX_PATH 100
#define MAX_PATH_LEN 4096
void shell_start(void);
char *_strcat(char *dest, char *src);
char *path(char *cmd);
void checkpath(char **arguments, char **env, struct stat **st, char *cmd_line);
void custom_error(char *cmd);
void numbering_print(int n);
void execute_command(char **env, char *cmd_line, char *delimiter);
void execution_cmd(char **env, char *cmd_part, char *limits);
void cusstimation_error(char *cmd);
#endif
