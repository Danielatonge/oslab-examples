#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int fuel = 0;
pthread_mutex_t mutexFuel;

void * car_fill() {
    
    while(fuel < 40) {
        printf("No fuel. Waiting ...\n");
        sleep(1);
    }
    pthread_mutex_lock(&mutexFuel);
    fuel -= 40;
    pthread_mutex_unlock(&mutexFuel);
    printf("Got fuel. Now left: %d\n", fuel);
}

void * fuel_fill() {
    printf("Filling tank\n");
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutexFuel);
        fuel+=15;
        pthread_mutex_unlock(&mutexFuel);
        printf("Filled fuel tank by %d\n", fuel);
        sleep(1);
    }
    
}
int main(void) {
    pthread_t t1, t2;
    pthread_mutex_init(&mutexFuel, NULL);

    pthread_create(&t1, NULL, &car_fill, NULL);
    pthread_create(&t2, NULL, &fuel_fill, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutexFuel);
    return 0;
}