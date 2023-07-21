#include <stdio.h>
#include <unistd.h>

/*
 * main - where our code starts
 * return: Always )
 */
int main(void)
{
	pid_t father_pid;
	father_pid = getppid();
	printf("My parent PID is: %u\n", father_pid);
	return (0);
}
