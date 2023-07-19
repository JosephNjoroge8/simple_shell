#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split-string - Split a stringinto words and returns an arry
 * @str: the input string to be split
 * @num_words: pointer to an integer
 * @delimiter: the character to split the string
 *
 * Return: Array of string containing each word or NULL
 */
char **split_string(const char *str, int *num_words, char delimiter)
{
	int i, j, count = 0;
	char **words = NULL;

	if (str == NULL || num_words == NULL)
	{
		return (NULL);
	}
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == delimiter)
		{
			count++;
		}
	}
	count++;
	words = (char **)malloc(count * sizeof(char *));
	if (words == NULL)
	{
		return (NULL);
	}
	int start = 0, word_length;
	for (i = 0, j = 0; str[i] != '\0'; i++)
	{
		if (str[i] == delimiter)
		{
			word_length = i - start;
			words[j] = (char *)malloc((word_length + 1) * sizeof(char));
			if (words[j] == NULL)
			{
				for (int k = 0; k < j; k++)
				{
					free(words[k]);
			        }
				free(words);
				return (NULL);
			}
			strncpy(words[j], &str[start], word_length);
			words[j][word_length] = '\0';
			j++;
			start = i + 1;
		}
	}
	word_length = i - start;
	words[j] = (char *)malloc((word_length + 1) * sizeof(char));
	if (words[j] == NULL)
	{
		for (int k = 0; k < j; k++)
		{
			free(words[k]);
		}
		free(words);
		return (NULL);
	}
	strncpy(words[j], &str[start], word_length);
	words[j][word_length] = '\0';
	j++;
	*num_words = count;
	return (words);
}

int main(void)
{
	char input[] = "hey lets test this sample string , I am loving it";
	int num_words, i;
	char **words = split_string(input, &num_words, ' ');

	if (words != NULL)
	{
		printf("number of words: %d\n", num_words);
		for (i = 0; i < num_words; i++)
		{
			printf("word %d: %s\n", i + 1, words[i]);
			free(words[i]);
		}
		free(words);
	} else {
		printf("Memory allocation failed.\n");
	}
	return (0);
}
