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
	token = strtok(s, delim);
	while (token != NULL && i < MAX_ARGS - 1)
	{
		tokens[i] = strdup(token);
		token = strtok(NULL, delim);
		i++;
	}
	tokens[i] = NULL;

	return (tokens);
}

/**
 * _getenv - our own getenv function
 * @var: the environment variable
 *
 * Return: the value of the environment variable or NULL
 */
char *_getenv(char *var)
{
	int i = 0;
	char **env = environ;
	char *key, *value, *temp, *res;

	if (var == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		temp = strdup(env[i]);
		key = strtok(temp, "=");
		value = strtok(NULL, "=");
		if (strcmp(key, var) == 0)
		{
			res = strdup(value);
			free(temp);
			return (res);
		}
		i++;
		free(temp);
	}

	return (NULL);
}

/**
 * find_path - finds the path of a command
 * @cmd: the command
 *
i* Return: the full path if found else NULL
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
	int err = 0;

	if (args == NULL || *args == NULL)
		return;
	path = find_path(args[0]);
	if (run_built_in(args) == 0)
		err = 1;
	if (path == NULL)
	{
		error(name, i, args[0]);
		err = 1;
	}
	if (!err)
	{
		pid = fork();
		if (pid == -1)
			error(name, i, "fork");
		else if (pid == 0)
		{
			if (execve(path, args, env) == -1)
				error(name, i, "execve");
		}
		else
			wait(NULL);
	}

}
