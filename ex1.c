#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void * func(void *arg) {
    printf("Test from threads\n");
    sleep(2);
    printf("Ending thread\n");
    return 0;
}
int main(void) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, &func, NULL);
    pthread_create(&t2, NULL, &func, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Good\n");
    return 0;
}