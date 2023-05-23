#include "shell.h"

/**
 * penv - prints the environment variables
 * @args: the args
 */
void penv(char **args)
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
}

/**
 * exiter - exits the program
 * @args: the argumenss
 */
void exiter(char **args)
{
	int i = 0;

	if (args[1] != NULL)
		i = atoi(args[1]);
	exit(i);
}
