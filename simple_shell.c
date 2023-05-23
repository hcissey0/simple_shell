#include "shell.h"

/**
 * main - the starting point of our simple shell
 * @argc: command line argument count
 * @argv: NULL terminated strnig array of commandline arguments
 * @env: the environment variablesi
 *
 * Return: 0 on success, 1 otherwise
 */
int main(__attribute__((unused)) int argc, char *argv[], char *env[])
{
	int i = 1;
	size_t len = 0;
	ssize_t rd;
	char *line = NULL, **tokens = NULL, *prompt = "$ ";

	if (isatty(STDIN_FILENO) == 1)
		_puts(prompt);
	while ((rd = _getline(&line, &len, stdin)) != -1)
	{
		if (strlen(line) > 1)
		{
			remove_newline(line);
			tokens = tokenizer(line, " ");
			run_command(tokens, argv[0], env, i);
			free(tokens);
		}
		i++;

		if (isatty(STDIN_FILENO) == 1)
			_puts(prompt);
	}
	if (rd == -1 && isatty(STDIN_FILENO) == 1)
		_putchar('\n');
	free(line);
	return (0);
}
