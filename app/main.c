#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include<io.h>
// #include <direct.h>
// #define getcwd _getcwd
// #define chdir _chdir
#else
#include <unistd.h>
#endif

#define MAX_INPUT_SIZE 100
#define MAX_TOKENS 10

bool is_builtin(char* command) {
    char* commands[] = {"cd", "echo", "exit", "pwd", "type"};
    int command_count = sizeof(commands) / sizeof(char*);
    for (int i = 0; i < command_count; i++) {
        if (strcmp(command, commands[i]) == 0) {
            return true;
        }
    }
    return false;
}

void handle_builtin(char** args) {
    if (strcmp(args[0], "exit") == 0) { // exit
        exit(0);
    } else if (strcmp(args[0], "echo") == 0) { // echo
        for (int j = 1; args[j] != NULL; j++) {
            printf("%s ", args[j]);
        }
        printf("\n");
    } else if (strcmp(args[0], "pwd") == 0) { // pwd
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            perror("pwd failed");
        }
    } else if (strcmp(args[0], "cd") == 0) { // cd
        if (args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd failed");
            }
        }
    } else if (strcmp(args[0], "type") == 0) { // type
        if (args[1] != NULL && is_builtin(args[1])) {
            printf("%s is a builtin command\n", args[1]);
        } else {
            printf("%s: command not found\n", args[1] ? args[1] : "type");
        }
    }
}

int main() {

        
    while (1) { // REPL (Read-Eval-Print-Loop)
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("%s $ ",cwd);
        fflush(stdout); // clear stdout stream

        // Wait for user input
        char input[MAX_INPUT_SIZE];
        fgets(input, MAX_INPUT_SIZE, stdin);

        input[strlen(input) - 1] = '\0'; // replacing default \n terminator with \0

        // Skip empty input
        if (strlen(input) == 0) {
            continue;
        }

        // Tokenize input
        char* token = strtok(input, " ");
        char* args[MAX_TOKENS];
        int i = 0;

        while (token != NULL && i < MAX_TOKENS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // NULL-terminate the array of tokens

        // Check if the command is a built-in
        if (is_builtin(args[0])) {
            handle_builtin(args);
        } else {
            printf("%s: command not found\n", args[0]);
        }
    }
    return 0;
}
