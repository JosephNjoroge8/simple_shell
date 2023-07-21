#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_string - split a string into wordsand returns an array of each word
 * @str: the input string to split
 * @num_words: pointer to an integer to store number of words
 *
 * Return: array of string or NULL
 */
char **split_string(const char *str, int *num_words)
{
	int i, count = 0;
	char **words = NULL;
	char *copy, *token;

	if (str == NULL || num_words == NULL) 
	{
		return (NULL);
	}
	copy = strdup(str);
	if (copy == NULL)
	{
		return (NULL);
	}
	token = strtok(copy, " ");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " ");
	}
	words = (char **)malloc(count * sizeof(char *));
	if (words == NULL)
	{
		free(copy);
		return (NULL);
	}
	token = strtok((char *)str, " ");
	for (i = 0; i < count; i++)
	{
		words[i] = strdup(token);
		if (words[i] == NULL)
		{
			for (int j = 0; j < i; j++)
			{
				free(words[j]);
			}
			free(words);
			free(copy);
			return (NULL);
		}
		token = strtok(NULL, " ");
	}
	free(copy);
	*num_words = count;
	return (words);
}

int main(void)
{
	char input[] = "this is a sample string to test my love for programming";
	int num_words, i;
	char **words = split_string(input, &num_words);

	if (words != NULL)
	{
		printf("number of words: %d\n", num_words);
		for (i = 0; i < num_words; i++)
		{
			printf("words %d: %s\n", i + 1, words[i]);
			free(words[i]);
		}
		free(words);
	}else {
		printf("Memory allocation failed.\n");
	}

	return (0);
}
