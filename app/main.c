#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  while(1){//REPL (Read-Eval-Print-Loop)
    printf("$ ");
    fflush(stdout);//clear stdout stream

    // Wait for user input
    char input[100];
    fgets(input, 100, stdin);

    input[strlen(input)-1]='\0'; //replacing default \n terminator with \0
    //exit
    if(!strcmp(input,"exit 0")){
      exit(0);
    }
    printf("%s: command not found\n",input);
  }
  return 0;
}
