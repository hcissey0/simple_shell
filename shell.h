#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_PATH_LEN 100
#define MAX_CMD_LEN 100
#define MAX_ARGS 10
#define BUF_SIZE 1024

extern char **environ;

/**
 * struct builtin - struct for the built-in commands
 * @cmd: the command
 * @func: the corresponding function
 */
typedef struct builtin
{
	char *cmd;
	int (*func)(char **);
} builtin_t;

/* simple_shell.c */
int check_spaces(char *);
char *find_path(char *);
void run_command(char **, char *, char **, int, int *);
int run_built_in(char **);

/* string0.c */
int _strlen(char *);
char *_strcpy(char *, char *);
char *_strcat(char *, char *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);

/* string1.c */
int _strcmp(char *, char *);
int _strncmp(char *, char *, int);
char *_strchr(char *, char);
char *_strstr(char *, char *);

/* helper0.c */
int _putchar(char);
int _puts(char *);
char *_getenv(char *);
ssize_t _getline(char **, size_t *, FILE *);
char *_strtok(char *, const char *);

/* helper1.c */
void remove_newline(char *);
char **tokenizer(char *, const char *);
void error(char *, int, char *, char *);

/* helper2.c */
int _setenv(char *, char *, int);
int _unsetenv(char *);
int cd(char **);

/* builtins.c */
int print_env(char **);
void free_tokens(char **);
int env_setter(char **);
int env_unsetter(char **);

#endif /* SHELL_H */
