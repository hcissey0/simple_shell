#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_PATH_LEN 200
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
	void (*func)(char **);
} builtin_t;

int _putchar(char);
int _puts(char *);
ssize_t _getline(char **, size_t *, FILE *);
char *_strtok(char *, const char *);
void remove_newline(char *);
char **tokenizer(char *, const char *);
char *_getenv(char *);
char *find_path(char *);
void run_command(char **, char *, char **, int);
void error(char *, int, char *);
void penv(char **);
void exiter(char **);
int run_built_in(char **);

#endif /* SHELL_H */
