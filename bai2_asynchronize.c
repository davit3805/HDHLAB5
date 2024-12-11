#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define max 20

int a[max];
int n = 0;
void *generate(void *arg)
{
    while (1)
    {
        if (n < max)
        {
            int x = rand() % 100;
            a[n++] = x;
            printf("Generate: Added a random number: %d. Total elements: %d\n", x, n);
        } else printf("Generate: Array is full!\n");
    }
}
void *takeout(void *arg)
{
    while (1)
    {
        if (n > 0)
        {
            int k = rand() % n;
            int x = a[k];
            for (int i = k; i < n - 1; i++) a[i] = a[i + 1];
            n--;
            printf("Take out: Removed a random number: %d. Total elements: %d\n", x, n);
        } else printf("Take out: Nothing in array a!\n");
    }
}
int main()
{
    srand(time(NULL));
    pthread_t gen, take;
    pthread_create(&gen, NULL, generate, NULL);
    pthread_create(&take, NULL, takeout, NULL);
    pthread_join(gen, NULL);
    pthread_join(take, NULL);
    return 0;
}