#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int _putchar(char);
int _puts(char *);
void remove_newline(char **);
char **tokenizer(char *, char *);

#endif /* SHELL_H */
