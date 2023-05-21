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

extern char **environ;

int _putchar(char);
int _puts(char *);
void remove_newline(char *);
char **tokenizer(char *, const char *);
char *_getenv(char *);
char *find_path(char *);

#endif /* SHELL_H */
