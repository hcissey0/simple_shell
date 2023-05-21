#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define MAX_PATH_LENGTH 200

void tokenize_command(char *command, char **arguments) {
    char *token = strtok(command, " ");
    int i = 0;
    while (token != NULL && i < MAX_ARGUMENTS - 1) {
        arguments[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    arguments[i] = NULL;
}

char *get_executable_path(char *command) {
    char *path = getenv("PATH");
    if (path != NULL) {
        char path_copy[MAX_PATH_LENGTH];
        strncpy(path_copy, path, MAX_PATH_LENGTH);
        char *path_token = strtok(path_copy, ":");
        while (path_token != NULL) {
            char executable_path[MAX_PATH_LENGTH];
            strncpy(executable_path, path_token, MAX_PATH_LENGTH);
            strncat(executable_path, "/", MAX_PATH_LENGTH);
            strncat(executable_path, command, MAX_PATH_LENGTH - strlen(executable_path));

            if (access(executable_path, X_OK) == 0) {
                char *result = malloc(strlen(executable_path) + 1);
                strcpy(result, executable_path);
                return result;
            }

            path_token = strtok(NULL, ":");
        }
    }
    return NULL;
}

void execute_command(char *command) {
    char *arguments[MAX_ARGUMENTS];
    tokenize_command(command, arguments);

    if (strcmp(arguments[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    }

    char *executable_path = get_executable_path(arguments[0]);
    if (executable_path != NULL) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (execve(executable_path, arguments, NULL) == -1) {
                perror("execve");
                _exit(EXIT_FAILURE);
            }
        } else {
            wait(NULL);
        }

        free(executable_path);
    } else {
        fprintf(stderr, "Command not found: %s\n", command);
    }
}

void read_command(char *command) {
    printf(":) ");
    fflush(stdout);

    ssize_t command_length = getline(&command, NULL, stdin);

    if (command_length == -1) {
        printf("\n");
        exit(EXIT_SUCCESS);
    }

    command[strcspn(command, "\n")] = '\0';
}

void handle_pipeline(char *command) {
    char *pipe_token = strtok(command, "|");
    while (pipe_token != NULL) {
        execute_command(pipe_token);
        pipe_token = strtok(NULL, "|");
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        read_command(command);
        handle_pipeline(command);
    }

    return 0;
}

