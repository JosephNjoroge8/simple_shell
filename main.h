#ifndef MAIN_H
#define MAIN_H
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
#define MAX_PATH_LEN 7000
void shell_start(void);
char *_strcat(char *dest, char *src);
char *path(char *cmd);
void set_environment(char **arguments);
void unset_environment(char **arguments);
void checkpath(char **arguments, char **env, struct stat **st, char *cmd_line);
void numbering_print(int n);
void execution_cmd(char **env, char *cmd_part, char *limits);
void cusstimation_error(char *cmd);
#endif
