#include "shell.h"

/**
 * remove_newline - removes the newline at the end of a string
 * @str: the string
 */
void remove_newline(char **str)
{
	int i = 0;

	if (*str == NULL)
		return;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\n')
		{
			(*str)[i] = '\0';
			break;
		}
		i++;
	}
}

/**
 * tokenizer - tokenizes the given string with respect to the given delimiter
 * @str: the given string
 * @delim: the delimiter
 *
 * Return: a NULL terminated array of strings
 */
char **tokenizer(char *str, char *delim)
{
	int i = 0;
	char *temp = str, **res;

	if (str == NULL)
		return (NULL);
	while (*temp)
	{
		if (strncmp(temp, delim, strlen(delim)) == 0)
			i++;
		temp++;
	}
	res = malloc(sizeof(char *) * (i + 1));
	i = 0;
	temp = strtok(str, delim);
	while (temp != NULL)
	{
		res[i++] = temp;
		temp = strtok(NULL, delim);
	}
	res[i] = NULL;

	return (res);
}
