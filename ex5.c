#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
int counter = 0;
int lock = 0;

pthread_mutex_t mutex;

void * traditional_critical() {
    for (int i = 0; i < 15000; i++){
        if (lock == 1) {
            // wait until the lock is 0
        }
        lock = 1;
        counter++;
        lock = 0;
    }
}

void * mutex_critical() {
    for (int i = 0; i < 1000000; i++){
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(void) {
    pthread_t th[4];
    int i;
    pthread_mutex_init(&mutex, NULL);

    for ( i = 0; i < 4; i++){
        if (pthread_create(&th[i], NULL, &mutex_critical, NULL)) {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n", i);
    }

    for ( i = 0; i < 4; i++){
        if(pthread_join(th[i], NULL)) {
            return 2;
        }
        printf("Thread %d has finished\n", i);
    }


    pthread_mutex_destroy(&mutex);
    printf("Value of counter: %d\n", counter);
    return 0;
}