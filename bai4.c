#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t mutex;
int x = 0;

void *processA(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        x = x + 1;
        if (x == 20) x = 0;
        printf("Process A: x = %d\n", x);
        pthread_mutex_unlock(&mutex);
    }
}

void *processB(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        x = x + 1;
        if (x == 20) x = 0;
        printf("Process B: x = %d\n", x);
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t A, B;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&A, NULL, processA, NULL);
    pthread_create(&B, NULL, processB, NULL);
    pthread_join(A, NULL);
    pthread_join(B, NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}