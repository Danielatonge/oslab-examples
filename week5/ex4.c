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
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t1, NULL, &mutex_critical, NULL);
    pthread_create(&t2, NULL, &mutex_critical, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);
    printf("Value of counter: %d\n", counter);
    return 0;
}