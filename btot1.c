#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int x1 = 2, x2 = 3, x3 = 4, x4 = 5, x5 = 6, x6 = 7;
int w, v, y, z, ans;

sem_t sem_w, sem_v, sem_y, sem_z;

void* compute_w(void* arg) 
{
    w = x1 * x2;
    printf("(a) w = x1 * x2 = %d\n", w);
    sem_post(&sem_w);  
    return NULL;
}

void* compute_v(void* arg) 
{
    v = x3 * x4;
    printf("(b) v = x3 * x4 = %d\n", v);
    sem_post(&sem_v);  
    return NULL;
}

void* compute_y(void* arg) 
{
    sem_wait(&sem_v);
    y = v * x5;
    printf("(c) y = v * x5 = %d\n", y);
    sem_post(&sem_v);
    sem_post(&sem_y);  
    return NULL;
}

void* compute_z(void* arg) 
{
    sem_wait(&sem_v);
    z = v * x6;
    printf("(d) z = v * x6 = %d\n", z);
    sem_post(&sem_v);
    sem_post(&sem_z);
    return NULL;
}

void* compute_y_final(void* arg) 
{
    sem_wait(&sem_w);
    sem_wait(&sem_y);
    y = w * y;
    printf("(e) y = w * y = %d\n", y);
    sem_post(&sem_y); 
    sem_post(&sem_w);
    return NULL;
}

void* compute_z_final(void* arg) 
{
    sem_wait(&sem_w);
    sem_wait(&sem_z);
    z = w * z;
    printf("(f) z = w * z = %d\n", z);
    sem_post(&sem_z); 
    sem_post(&sem_w);
    return NULL;
}

void* compute_ans(void* arg) 
{
    sem_wait(&sem_y);
    sem_wait(&sem_z);
    ans = y + z;
    printf("(g) ans = y + z = %d\n", ans);
    return NULL;
}

int main() 
{
    pthread_t thread_w, thread_v, thread_y, thread_z, thread_y_final, thread_z_final, thread_ans;

    sem_init(&sem_w, 0, 0);   
    sem_init(&sem_v, 0, 0); 
    sem_init(&sem_y, 0, 0);   
    sem_init(&sem_z, 0, 0); 

    pthread_create(&thread_w, NULL, compute_w, NULL);
    pthread_create(&thread_v, NULL, compute_v, NULL);
    pthread_create(&thread_y, NULL, compute_y, NULL);
    pthread_create(&thread_z, NULL, compute_z, NULL);
    pthread_create(&thread_y_final, NULL, compute_y_final, NULL);
    pthread_create(&thread_z_final, NULL, compute_z_final, NULL);
    pthread_create(&thread_ans, NULL, compute_ans, NULL);

    pthread_join(thread_w, NULL);
    pthread_join(thread_v, NULL);
    pthread_join(thread_y, NULL);
    pthread_join(thread_z, NULL);
    pthread_join(thread_y_final, NULL);
    pthread_join(thread_z_final, NULL);
    pthread_join(thread_ans, NULL);

    sem_destroy(&sem_w);
    sem_destroy(&sem_v);
    sem_destroy(&sem_y);
    sem_destroy(&sem_z);

    return 0;
}
