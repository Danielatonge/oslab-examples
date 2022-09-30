#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
// locking a mutex twice also leads to a deadlock
int fuel = 50;
pthread_mutex_t mutexFuel;
int water = 50;
pthread_mutex_t mutexWater;



void * fill() {
    if( rand() % 2 == 0) {
        pthread_mutex_lock(&mutexFuel);
        sleep(1);
        pthread_mutex_lock(&mutexWater);
    } else {
        pthread_mutex_lock(&mutexWater);
        sleep(1);
        pthread_mutex_lock(&mutexFuel);
    }
    fuel += 100;
    printf("Incremented by: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
    pthread_mutex_unlock(&mutexWater);
}


int main(void) {
    srand(time(NULL));
    pthread_t t1, t2;
    pthread_mutex_init(&mutexFuel, NULL);

    pthread_create(&t1, NULL, &fill, NULL);
    pthread_create(&t2, NULL, &fill, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutexFuel);
    pthread_mutex_destroy(&mutexWater);
    return 0;
}