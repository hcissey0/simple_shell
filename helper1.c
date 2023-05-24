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
		return (cmd);
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
			free(dirs);
			cmd = full;
			return (full);
		}
		i++;
	}
	free(full);
	free(path);
	free(dirs);
	return (NULL);
}

/**
 * run_command - runs the command
 * @args: the commands
 * @name: the name of the caller
 * @env: environmen variables ofthe caller
 * @i: the command count
 */
void run_command(char **args, char *name, char **env, int i)
{
	char *path;
	pid_t pid;
	int err = 0, b = 1;

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
	}
	if (!err)
	{
		pid = fork();
		if (pid == -1)
			error(name, i, "fork", "Can't create another process");
		else if (pid == 0)
		{
			if (execve(path, args, env) == -1)
				error(name, i, "execve", "No such file or directory");
		}
		else
			wait(NULL);
	}
	free(path);
}
