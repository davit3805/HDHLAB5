#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int x = 0;

void *processA(void *arg)
{
    while(1)
    {
        x = x + 1;
        if (x == 20) x = 0;
        printf("Process A: x = %d\n", x);
    }
}

void *processB(void *arg)
{
    while(1)
    {
        x = x + 1;
        if (x == 20) x = 0;
        printf("Process B: x = %d\n", x);
    }
}

int main()
{
    pthread_t A, B;
    pthread_create(&A, NULL, processA, NULL);
    pthread_create(&B, NULL, processB, NULL);
    pthread_join(A, NULL);
    pthread_join(B, NULL);
    return 0;
}