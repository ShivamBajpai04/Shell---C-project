#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main() {
    while (1) { // REPL (Read-Eval-Print-Loop)
        printf("$ ");
        fflush(stdout); // clear stdout stream

        // Wait for user input
        char input[100];
        fgets(input, 100, stdin);

        input[strlen(input) - 1] = '\0'; // replacing default \n terminator with \0 as it messes up the command not found output by making the message appear in the next line
        if (strlen(input) == 0) {
          continue;
        }
        if (!strncmp(input, "exit", 4)) { // exit
            return 0;
        } else if (!strncmp(input, "echo ", 5)) { //echo
            printf("%s\n", input + 5);
        } else if (!strncmp(input, "type ", 5)) { //type
            if (is_builtin(input + 5)) {
                printf("%s is a builtin command\n", input + 5);
                continue;
            } else {
                printf("%s: command not found\n", input + 5);
                continue;
            }
        } else { //invalid command
            printf("%s: command not found\n", input);
        }
    }
    return 0;
}
