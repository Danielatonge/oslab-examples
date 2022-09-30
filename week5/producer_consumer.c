#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define THREAD_NUM 2

pthread_mutex_t mutexBuffer;
sem_t semEmpty;
sem_t semFull;

int buffer[10];
int count = 0;

void *producer(void * args) {
    while(1) {
        // Produce
        int x = rand() % 100;

        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutexBuffer);
        // Add to the buffer

        printf("Produced %d\n", x);
        buffer[count] = x;
        count++;

        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);
    }
}

void *consumer(void * args) {
    while(1) {
        int y;

        sem_wait(&semFull);
        pthread_mutex_lock(&mutexBuffer);
        // Remove from the buffer
        y = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);

        // Consume
        printf("Consumed %d\n", y);
        sleep(1);
    }
}

int main(void) {
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);

    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if(i % 2 == 0) {
            if (pthread_create(&th[i], NULL, &producer, NULL)) {
                perror("Failed to create thread");
                return 1;
            }
        } else {
            if (pthread_create(&th[i], NULL, &consumer, NULL)) {
                perror("Failed to create thread");
                return 1;
            }
        }
    }
    
    for (int i = 0; i < THREAD_NUM; i++) {
        if(pthread_join(th[i], NULL)) {
            return 2;
        }
    }

    pthread_mutex_destroy(&mutexBuffer);
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    return 0;
}
