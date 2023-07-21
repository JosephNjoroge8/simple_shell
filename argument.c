#include "main.h"
/**
 *handle_arguments - handles command line arguments
 *@argc:argument count
 *@argv:arguments vector
 */
void handle_arguments(int argc, char *argv[])
{
	int i;

	printf("%d\n", argc);
	for (i = 0; i < argc; i++)
	{
		printf("%d: %s\n", i, argv[i]);
	}
}
