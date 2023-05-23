#include "shell.h"

/**
 * _putchar - prints a character to stdout
 * @c: the char
 *
 * Return: 1
 */
int _putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

/**
 * _puts - prints a string to stdout
 * @str: the string to print
 *
 * Return: the number of characters printed
 */
int _puts(char *str)
{
	int i = 0;

	if (str == NULL)
		return (i);
	while (str[i] != '\0')
		_putchar(str[i++]);

	return (i);
}

/**
 * error - prints error
 * @name: name of the program
 * @i: command count error
 * @str: error string
 */
void error(char *name, int i, char *str)
{
	dprintf(STDERR_FILENO, "%s: %i: %s: ", name, i, str);
	perror(NULL);
}

/**
 * _getline - our own getline function
 * @lineptr: destination
 * @n: number of chars read
 * @stream: the file stream to read from
 *
 * Return: number of characters read, -1 on error
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char buffer[BUF_SIZE], *new_lineptr;
	size_t total = 0, len;

	if (*lineptr == NULL || *n == 0)
	{
		*n = BUF_SIZE;
		*lineptr = malloc(sizeof(char) * (*n));
		if (*lineptr == NULL)
			return (-1);
	}
	while (fgets(buffer, BUF_SIZE, stream))
	{
		len = strlen(buffer);
		if (total + len + 1 > *n)
		{
			new_lineptr = realloc(*lineptr, sizeof(char) * (*n + BUF_SIZE));
			if (new_lineptr == NULL)
				return (-1);
			*lineptr = new_lineptr;
			*n += BUF_SIZE;
		}
		strcpy(*lineptr + total, buffer);
		total += len;
		if ((*lineptr)[total -1] == '\n')
			return (total);
	}
	
	return (-1);
}

/**
 * _strtok - our own strtok
 * @str: the string
 * @delim: the delimiter
 *
 * Return: a string on success or NULL
 */
char *_strtok(char *str, const char *delim)
{
	/*
	static char *last = NULL;
	char *token;

	if (str != NULL)
		last = str;
	if (last == NULL)
		return (NULL);
	while (*last != '\0')
	{
		if (strchr(delim, *last) != NULL)
		{
			*last = '\0';
			last++;
			return (token);
		}
		last++;
	}
	return (token);
	*/
	static char *last;
	char *token;

	if (str == NULL)
		str = last;
	else
		last = str;
	if (last == NULL)
		return (NULL);
	while (*str != '\0' && strchr(delim, *str))
		str++;
	if (*str == '\0')
		return (NULL);
	token = str;
	str = strchr(str, *delim);
	if (str != NULL)
		*str++ = '\0';
	last = str;
	return (token);
}
