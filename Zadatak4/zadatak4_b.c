#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char** cmdArguments = malloc((argc + 1) * sizeof(char*));
    cmdArguments[0] = malloc((strlen("./zadatak4_a") + 1) * sizeof(char));
    strcpy(cmdArguments[0], "./zadatak4_a");
    for (int i = 1; i < argc; ++i) {
        cmdArguments[i] = malloc((strlen(argv[i]) + 1) * sizeof(char));
        strcpy(cmdArguments[i], argv[i]);
    }
    cmdArguments[argc] = NULL;
    int pid = fork();
    if (pid == 0) {
        if (execv("./zadatak4_a", cmdArguments) < 0) {
            printf("An error occured! Exiting...\n");
            exit(1);
        }
    } else wait(NULL);
    for (int i = 0; i < argc; ++i) free(cmdArguments[i]);
    free(cmdArguments);
    return 0;
}
