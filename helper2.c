#include "shell.h"

/**
 * run_built_in - runs a built-in command
 * @args: the list of built-in commands
 *
 * Return: 0 on success, 1 otherwise
 */
int run_built_in(char **args)
{
	int i = 0;
	builtin_t builtins[] = {
		{"exit", exiter}, {"env", penv},
		{NULL, NULL}
	};

	while (builtins[i].cmd != NULL)
	{
		if (strcmp(args[0], builtins[i].cmd) == 0)
		{
			builtins[i].func(args);
			return (0);
		}
		i++;
	}
	return (1);
}
