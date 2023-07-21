#include <stdio.h>

/*
 * main- start of our program
 * j: value to loop
 * return: Always 0
 */
int main(int argc, char **argv)
{
	int j = 1;
	while (argv[j] != NULL)
	{
		printf("%s ", argv[j]);
		j++;
	}
	printf("\n");
	return (0);
}
