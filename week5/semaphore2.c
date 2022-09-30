#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define THREAD_NUM 16

sem_t semaphore;

void *tfunc(void *arg) {
    printf("(%d) Waiting in the login queue\n", *(int*)arg);
    sem_wait(&semaphore);
    printf("(%d) Logged in\n", *(int*)arg);
    sleep(rand() % 5 + 1);
    printf("(%d) Logged out\n", *(int*)arg);
    sem_post(&semaphore);
    free(arg);
}

int main(void) {
    pthread_t th[THREAD_NUM];
    sem_init(&semaphore, 0, 12);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        int *arg = malloc(sizeof(int));
        *arg = i;
        if (pthread_create(&th[i], NULL, &tfunc, arg)) {
            perror("Failed to create thread");
            return 1;
        }
    }
    
    for (int i = 0; i < THREAD_NUM; i++) {
        if(pthread_join(th[i], NULL)) {
            return 2;
        }
    }

    sem_destroy(&semaphore);
    return 0;
}
