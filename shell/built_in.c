#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include "shell.h"

int built_in(char **command){
    if (strcmp(command[0], "exit") == 0) {
        should_run = 0;
        return 1;
    }
    if (strcmp(command[0], "cd") == 0) {
        if (chdir(command[1]) != 0) {
            perror("cd failed");
        }
        return 1;
    }
    if (strcmp(command[0], "pwd") == 0) {
        printf("%s\n", getcwd(NULL, 0));
        return 1;
    }
    if (strcmp(command[0], "help") == 0) {
        printf("Unix Shell - A simple shell implementation\n");
        printf("Supported built-in commands:\n");
        printf("- cd\n");
        printf("- pwd\n");
        printf("- help\n");
        printf("- exit\n");
        return 1;
    }
    return 0;
}