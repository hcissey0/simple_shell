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
	int i = 1, ex = 0;
	size_t len = 0;
	ssize_t rd;
	char *line = NULL, **tokens = NULL, *prompt = "$ ";

	if (isatty(STDIN_FILENO) == 1)
		_puts(prompt);
	while ((rd = _getline(&line, &len, stdin)) != -1)
	{
		if (strlen(line) > 1 && check_spaces(line) != 0)
		{
			remove_newline(line);
			tokens = tokenizer(line, " ");
			if (tokens == NULL)
				continue;
			if (strcmp(tokens[0], "exit") == 0)
			{
				if (tokens[1] != NULL)
					ex = atoi(tokens[1]);
				free_tokens(tokens);
				break;
			}
			run_command(tokens, argv[0], env, i, &ex);
			free_tokens(tokens);
		}
		i++;
		if (isatty(STDIN_FILENO) == 1)
			_puts(prompt);
	}
	if (rd == -1 && isatty(STDIN_FILENO) == 1)
		_putchar('\n');
	free(line);
	return (ex);
}

/**
 * check_spaces - checks if a newline terminated string is all spaces
 * @str: the string
 *
 * Return: 0 if true otherwise 1
 */
int check_spaces(char *str)
{
	unsigned int i = 0;

	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

/**
 * find_path - finds the path of a command
 * @cmd: the command
 *
 * Return: the full path if found else NULL
 */
char *find_path(char *cmd)
{
	char *full, *path, **dirs;
	int i = 0, len;

	full = NULL;
	path = NULL;
	dirs = NULL;
	if (cmd == NULL)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (strdup(cmd));
	path = _getenv("PATH");
	dirs = tokenizer(path, ":");
	while (dirs[i] != NULL)
	{
		len = strlen(dirs[i]) + strlen(cmd) + 2;
		full = realloc(full, (sizeof(char) * len));
		strcpy(full, dirs[i]);
		strcat(full, "/");
		strcat(full, cmd);
		if (access(full, X_OK) == 0)
		{
			free_tokens(dirs);
			free(path);
			return (full);
		}
		i++;
	}
	free(full);
	free(path);
	free_tokens(dirs);
	return (NULL);
}

/**
 * run_command - runs the command
 * @args: the commands
 * @name: the name of the caller
 * @env: environmen variables ofthe caller
 * @i: the command count
 * @ex: exit status
 */
void run_command(char **args, char *name, char **env, int i, int *ex)
{
	char *path;
	pid_t pid;
	int err = 0, b = 1, status;

	if (args == NULL || *args == NULL)
		return;
	b = run_built_in(args);
	if (b == -1)
	{
		error(name, i, args[0], "error");
		err = 1;
	}
	else if (b == 0)
		err = 1;
	path = find_path(args[0]);
	if (path == NULL && !err)
	{
		error(name, i, args[0], "not found");
		err = 1;
		*ex = 127;
		return;
	}
	if (!err)
	{
		pid = fork();
		if (pid == -1)
			error(name, i, "fork", "Can't create another process");
		else if (pid == 0)
			if (execve(path, args, env) == -1)
				perror(args[0]);
		else
		{
			if (wait(&status) == -1)
				perror("wait");
			else if (WIFEXITED(status))
				*ex = WEXITSTATUS(status);
		}
	}
	free(path);
}

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
		{"env", print_env},
		{"setenv", env_setter}, {"unsetenv", env_unsetter},
		{"cd", cd},
		{NULL, NULL}
	};

	while (builtins[i].cmd != NULL)
	{
		if (strcmp(args[0], builtins[i].cmd) == 0)
		{
			if (builtins[i].func(args) == -1)
				return (-1);
			return (0);
		}
		i++;
	}
	return (1);
}
