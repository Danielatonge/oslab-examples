#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define THREAD_NUM 4

sem_t semaphore;

void *tfunc(void *arg) {
    sem_wait(&semaphore);
    sleep(2);
    printf("Hello from thread %d\n", *(int*)arg);
    sem_post(&semaphore);
    free(arg);
}

int main(void) {
    pthread_t th[THREAD_NUM];
    sem_init(&semaphore, 0, 2);
    // Second argument 0 - one process having multiple threads
    // 1 - many processes having multiple threads
    // third argument - initial value of the semaphore
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
