#include "main.h"
/**
 *numbering_print - number printing
 *@n: number the print
 */
void numbering_print(int n)
{
	char num;

	if (n > 9)
	{
		numbering_print(n / 10);
	}

	num = (n % 10) + '0';
	write(2, &num, 1);
}
