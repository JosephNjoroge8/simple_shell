#include "main.h"
/**
 *customation_error - write errors
 *@cmd: command
 */
void cusstimation_error(char *cmd)
{
	static int errors;
	char *prefix = "./hsh: ";
	int cmd_len = 0;

	while (cmd[cmd_len])
		cmd_len++;

	errors++;
	write(STDERR_FILENO, prefix, 7);
	numbering_print(errors);	
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, cmd_len);
	write(STDERR_FILENO, ": not found\n", 12);
}
