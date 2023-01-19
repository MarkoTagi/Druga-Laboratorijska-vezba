#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

struct printArguments {
    char* word;
    int index;
};

void* printWord(void* arg) {
    struct printArguments* pa = (struct printArguments*)arg;
    //printf("In thread #%d: i = %d.\n",pa->index, pa->index);
    pa->index < 4 ? printf("%s ", pa->word) : printf("%s\n", pa->word);
    free(pa->word);
    sem_post(&sem);
}

int main() {
    char* inputText[5] = {"Ovo", "je", "test", "za", "niti!"};
    pthread_t threads[5];
    sem_init(&sem, 0, 1);
    for (int i = 0; i < 5; ++i) {
        sem_wait(&sem);
        struct printArguments pa;
        pa.index = i;
        pa.word = malloc((strlen(inputText[i]) + 1) * sizeof(char));
        strcpy(pa.word, inputText[i]);
        //printf("Creating thread #%d...\n", i);
        pthread_create(&threads[i], NULL, printWord, &pa);
    }
    for (int i = 0; i < 5; ++i) pthread_join(threads[i], NULL);
    sem_destroy(&sem);
    return 0;
}
