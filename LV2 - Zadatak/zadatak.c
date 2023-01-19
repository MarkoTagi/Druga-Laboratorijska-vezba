#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

struct ThreadArgs {
    int* array;
    int itemCount;
};

void printArray(int inputArray[], int arraySize) {
    printf("[ ");
    for (int i = 0; i < arraySize - 1; ++i) printf("%d, ", inputArray[i]);
    printf("%d ]\n", inputArray[arraySize - 1]);
}

int stringToInteger(const char* string) {
    int stringLength = 0;
    while (string[stringLength] != '\0') ++stringLength;
    int theNumber = 0;
    for (int i = 0; i < stringLength; ++i) {
        if ((string[i] < '0' || string[i] > '9') && string[i] != '-') {
            printf("Invalid format, you've entered a character(%c).\n", string[i]);
            return 0;
        }
        int aDigit = (string[i] == '-') ? -(string[++i] - '0') : string[i] - '0';
        theNumber += aDigit * pow(10, stringLength - 1 - i);
    }
    return theNumber;
}

void* threadFunction(void* arg) {
    int* theArray = ((struct ThreadArgs*)arg)->array;
    int itemCount = ((struct ThreadArgs*)arg)->itemCount;
    int total = 0; double average;
    for (int i = 0; i < itemCount; ++i) total += theArray[i];
    average = (double)total / itemCount;
    printf("Total: %d.\nAverage: %lf.\n", total, average);
}

int main(int argc, char* argv[]) {
    int inputArray[argc - 1]; int arraySize = argc - 1;
    for (int i = 0; i < arraySize; ++i) inputArray[i] = stringToInteger(argv[i + 1]);
    //printf("The array...\n\t");
    //printArray(inputArray, arraySize);
    pthread_t thread_id;
    struct ThreadArgs ta;
    ta.array = inputArray;
    ta.itemCount = arraySize;
    pthread_create(&thread_id, NULL, threadFunction, &ta);
    pthread_join(thread_id, NULL);
    return 0;
}
