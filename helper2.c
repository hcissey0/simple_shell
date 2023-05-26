#include "shell.h"

/**
 * _setenv - our setenv
 * @envname: name of the env
 * @envval: value to be set
 * @overwrite: flag for overwriting
 *
 * Return: 0 on success, -1 otherwise
 */
int _setenv(char *envname, char *envval, int overwrite)
{
	int i = 0, fnd = 0;
	char *env;

	if (envname == NULL || envval == NULL)
		return (-1);
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], envname, strlen(envname)) == 0)
		{
			fnd = 1;
			break;
		}
		i++;
	}
	if (fnd && !overwrite)
		return (0);
	env = malloc(sizeof(char) * (strlen(envname) + strlen(envval) + 2));
	strcpy(env, envname);
	strcat(env, "=");
	strcat(env, envval);
	environ[i] = env;
	if (!fnd)
		environ[i + 1] = NULL;
	return (0);
}

/**
 * _unsetenv - our unsetenv function
 * @envname: the name of the environment varible
 *
 * Return: 0 on success, -1 otherwise
 */
int _unsetenv(char *envname)
{
	int i = 0, j = 0, fnd = 0;

	if (envname == NULL)
		return (-1);
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], envname, strlen(envname)) == 0)
		{
			fnd = 1;
			break;
		}
		i++;
	}
	if (!fnd)
		return (0);
	for (j = i; environ[j] != NULL; j++)
		environ[j] = environ[j + 1];
	return (0);
}

/**
 * cd - change directory
 * @args: the arguments
 *
 * Return: 0 on success, -1 otherwise
 */
int cd(char **args)
{
	char *old_pwd = malloc(sizeof(char) * (MAX_PATH_LEN + 1));

	old_pwd = _getenv("PWD");
	_setenv("OLDPWD", old_pwd, 1);
	if (args[1] == NULL)
	{
		if (chdir(_getenv("HOME")) == -1)
			return (-1);
		_setenv("PWD", _getenv("HOME"), 1);
	}
	else if (args[1][0] == '-')
	{
		if (chdir(_getenv("OLDPWD")) == -1)
			return (-1);
		_setenv("PWD", _getenv("OLDPWD"), 1);
	}
	else
	{
		if (chdir(args[1]) == -1)
			return (-1);
		_setenv("PWD", _getenv(args[1]), 1);
	}

	return (0);
}
