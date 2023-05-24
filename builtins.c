#include "shell.h"

/**
 * print_env - prints the environment variables
 * @args: the args
 *
 * Return: Always 0
 */
int print_env(char **args)
{
	int i = 0;
	char *temp;

	(void)args;
	while (environ[i] != NULL)
	{
		temp = strdup(environ[i]);
		_puts(temp);
		_puts("\n");
		free(temp);
		i++;
	}

	return (0);
}

/**
 * exiter - exits the program
 * @args: the arguments
 *
 * Return: Always 0
 */
int exiter(char **args)
{
	int i = 0;

	if (args[1] != NULL)
		i = atoi(args[1]);
	exit(i);

	return (0);
}

/**
 * env_setter - our own setenv command
 * @args: the arguments
 *
 * Return: 0 on success, -1 on error
 */
int env_setter(char **args)
{
	if (args[1] == NULL || args[2] == NULL || args[3] != NULL)
		return (-1);
	return (_setenv(args[1], args[2], 1));
}

/**
 * env_unsetter - our own unsetenv command handler
 * @args: the commandlien arguments
 *
 * Return: 0 on success, -1 otherwise
 */
int env_unsetter(char **args)
{
	if (args[1] == NULL || args[2] != NULL)
		return (-1);
	return (_unsetenv(args[1]));
}
