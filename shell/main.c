#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include "shell.h"

int should_run=1;

int main() {
    char **command;
    char *input;
    pid_t child_pid;
    int stat_loc;
    int background = 0;

    while (should_run) {
        input = readline("unixsh> ");
        fflush(stdout);

        if (strlen(input) == 0) {
            free(input);
            free(command);
            continue;
        }

        command = parse_input(input);

        int argc = 0;
        while (command[argc] != NULL) {
            argc++;
        }
        // In parse_input.c, add logic to detect '&'
        if (argc > 1 && strcmp(command[argc - 1], "&") == 0) {
            command[argc - 1] = NULL; // Remove '&' from arguments
            background = 1;
        }else {
            background = 0;
        }

        if (built_in(command)) {
            free(input);
            free(command);
            continue;
        }

        child_pid = fork();
        if (child_pid == 0) {
            /* Never returns if the call is successful */
            execvp(command[0], command);
            printf("This won't be printed if execvp is successul\n");
        } else {
            if (!background) {
                waitpid(child_pid, &stat_loc, WUNTRACED);
            } else {
                printf("[%d] %s running in background\n", child_pid, command[0]);
                printf("[%d] %s completed\n", child_pid, command[0]);

            }
        }

        free(input);
        free(command);
    }

    return 0;
}

