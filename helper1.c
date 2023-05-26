#include "shell.h"

/**
 * remove_newline - removes the newline at the end of a string
 * @str: the string
 */
void remove_newline(char *str)
{
	int len;

	/* str[strcspn(str, "\n")] = '\0'; */
	if (str == NULL)
		return;
	len = strlen(str);
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
}

/**
 * tokenizer - tokenizes the given string with respect to the given delimiter
 * @str: the given string
 * @delim: the delimiter
 *
 * Return: a NULL terminated array of strings
 */
char **tokenizer(char *str, const char *delim)
{
	int i = 0;
	char *token, *s = str, **tokens = NULL;

	if (str == NULL || delim == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * (MAX_ARGS + 1));
	if (tokens == NULL)
	{
		perror("malloc");
		exit(1);
	}
	token = _strtok(s, delim);
	while (token != NULL && i < MAX_ARGS - 1)
	{
		tokens[i] = strdup(token);
		token = _strtok(NULL, delim);
		i++;
	}
	tokens[i] = NULL;

	return (tokens);
}

/**
 * error - prints error
 * @name: name of the program
 * @i: command count error
 * @str: error string
 * @msg: the error message
 */
void error(char *name, int i, char *str, char *msg)
{
	dprintf(STDERR_FILENO, "%s: %i: %s: %s\n", name, i, str, msg);
}
