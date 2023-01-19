#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

struct sortArguments {
    int** m_matrix;
    int m_rowCount, m_columnCount, m_rowIndex;
};

void printMatrix(int** matrix, int rowCount, int columnCount) {
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void* sortMatrixRow(void* arg) {
    int** theMatrix = ((struct sortArguments*)arg)->m_matrix;
    int rowCount = ((struct sortArguments*)arg)->m_rowCount;
    int columnCount = ((struct sortArguments*)arg)->m_columnCount;
    int rowIndex = ((struct sortArguments*)arg)->m_rowIndex;
    printf("Sorting row#%d\n", rowIndex);
    for (int i = 0; i < columnCount - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < columnCount; ++j) {
            minIndex = theMatrix[rowIndex][j] < theMatrix[rowIndex][minIndex] ? j : minIndex;
        }
        if (minIndex != i) {
            int temp = theMatrix[rowIndex][i];
            theMatrix[rowIndex][i] = theMatrix[rowIndex][minIndex];
            theMatrix[rowIndex][minIndex] = temp;
        }
    }
    sem_post(&sem);
}

int main() {
    sem_init(&sem, 0, 1);
    int rowCount, columnCount;
    printf("Enter the number of rows: ");
    scanf("%d", &rowCount);
    printf("Enter the number of columns: ");
    scanf("%d", &columnCount);
    int** matrix = malloc(rowCount * sizeof(int*));
    for (int i = 0; i < rowCount; ++i) matrix[i] = malloc(columnCount * sizeof(int));
    printf("Enter the elements...\n");
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            printf("Element[%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("Unsorted matrix...\n");
    printMatrix(matrix, rowCount, columnCount);
    pthread_t* threads = malloc(rowCount * sizeof(pthread_t));
    struct sortArguments args;
    args.m_matrix = matrix; args.m_rowCount = rowCount; args.m_columnCount = columnCount;
    for (int i = 0; i < rowCount; ++i) {
        sem_wait(&sem);
        args.m_rowIndex = i;
        pthread_create(&threads[i], NULL, sortMatrixRow, &args);
    }
    for (int i = 0; i < rowCount; ++i) pthread_join(threads[i], NULL);
    printf("Sorted matrix...\n");
    printMatrix(matrix, rowCount, columnCount);
    for (int i = 0; i < rowCount; ++i) free(matrix[i]);
    free(matrix);
    free(threads);
    sem_destroy(&sem);
    return 0;
}
