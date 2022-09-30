#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int counter = 0;

pthread_mutex_t mutex;

void * func(void *arg) {
    for (int i = 0; i < 15000000; i++){
        // critical
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);

        // read counter
        // increment
        // write counter
    }
}
int main(void) {
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t1, NULL, &func, NULL);
    pthread_create(&t2, NULL, &func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Value of counter: %d\n", counter);
    pthread_mutex_destroy(&mutex);

    // pthread_exit(NULL);



    return 0;
}