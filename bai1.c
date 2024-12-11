#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MSSV 1802

sem_t semA, semB;
int products = 0, sells = 0;

void *produce(void *arg)
{
    while (1)
    {
        sem_wait(&semB);
        products++;
        printf("Produced: %d \n", products);
        sem_post(&semA);
    }
}

void *consume(void *arg)
{
    while (1)
    {
        sem_wait(&semA);
        sells++;
        printf("Consumed: %d \n", sells);
        sem_post(&semB);
    }
}

int main()
{
    pthread_t producer, consumer;
    sem_init(&semA, 0, 0);
    sem_init(&semB, 0, MSSV);
    pthread_create(&producer, NULL, produce, NULL);
    pthread_create(&consumer, NULL, consume, NULL);
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
    sem_destroy(&semA);
    sem_destroy(&semB);
    return 0;
}