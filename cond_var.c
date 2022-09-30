#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
// condition variables
// wait
// broadcast
// signal

int fuel = 0;
pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;

void * car_fill() {
    
    pthread_mutex_lock(&mutexFuel);
    while(fuel < 40) {
        printf("No fuel. Waiting ...\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
        // pthread_mutex_unlock(&mutexFuel);
        // wait for signal on condFuel
        // pthread_mutex_lock(&mutexFuel);
    }
    fuel -= 40;
    printf("Got fuel. Now left: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}

void * fuel_fill() {
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutexFuel);
        fuel+=15;
        pthread_mutex_unlock(&mutexFuel);
        printf("Filled fuel tank by %d\n", fuel);
        pthread_cond_signal(&condFuel);
    }
    
}
int main(void) {
    pthread_t t1, t2;
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);

    pthread_create(&t1, NULL, &car_fill, NULL);
    pthread_create(&t2, NULL, &fuel_fill, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}