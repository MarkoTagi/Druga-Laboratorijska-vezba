#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    char userInput[100];
    printf("Enter the file's name: ");
    scanf("%s", userInput);
    int pid = fork();
    if (pid == 0) {
        if (execlp("cp", "cp", userInput, "./tmp", NULL) < 0) {
            printf("An error occured. Exiting...\n");
            exit(1);
        }
    } else wait(NULL);
    return 0;
}
