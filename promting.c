#include "main.h"
/**
 *shell_start - write a prompt
 */
void shell_start(void)
{
	if (isatty(STDIN_FILENO) != 0)
		write(STDOUT_FILENO, "$ ", 2);
}
