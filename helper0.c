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
