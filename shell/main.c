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

    while (should_run) {
        input = readline("unixsh> ");
        fflush(stdout);
        command = parse_input(input);

        if (built_in(command)) {
            continue;
        }

        child_pid = fork();
        if (child_pid == 0) {
            /* Never returns if the call is successful */
            execvp(command[0], command);
            printf("This won't be printed if execvp is successul\n");
        } else {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }

        free(input);
        free(command);
    }

    return 0;
}

