#include "shell.h"

/**
 * main - the starting point of our simple shell
 * @argc: command line argument count
 * @argv: NULL terminated strnig array of commandline arguments
 * @env: the environment variables
 *
 * Return: 0 on success, 1 otherwise
 */
int main(__attribute__((unused)) int argc, char *argv[], char *env[])
{
	int status = 0, i = 1;
	size_t len = 0;
	ssize_t rd;
	pid_t pid;
	char *line = NULL, **tokens = NULL, *prompt = "$ ";

	if (isatty(STDIN_FILENO) == 1)
		_puts(prompt);
	while ((rd = getline(&line, &len, stdin)) != -1)
	{
		if (strlen(line) > 1)
		{
			remove_newline(line);
			tokens = tokenizer(line, " ");
			pid = fork();
			if (pid == 0)
			{
				if (execve(tokens[0], tokens, env) == -1)
				{
					perror(argv[0]);
					free(tokens);
				}
				break;
			}
			else
				wait(&status);
			free(tokens);
		}
		i++;
		_puts(prompt);
		fflush(stdin);
	}
	if (rd == -1 && isatty(STDIN_FILENO) == 1)
		_putchar('\n');
	free(line);
	return (0);
}
