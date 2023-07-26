#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define MAX_INPUT 100
#define MAX_ARGS 64
char *write_input();
void execute_command(char *command);
#define MAX_PATH 500
#define MAX_PATH_LEN 1024
#endif
