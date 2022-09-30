#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

int prime[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void * unique(void *arg) {
    int index = *(int *)arg;
    printf("%d\n", prime[index]);
    *(int *)arg = prime[index];
    return (void *)arg;
}

int main(void) {
    int * res;
    pthread_t th[10];
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        int *arg = malloc(sizeof(int));
        *arg = i;
        if (pthread_create(&th[i], NULL, &unique, arg)) {
            perror("Failed to create thread");
            return 1;
        }
    }
    
    
    for (int i = 0; i < 10; i++) {
        if(pthread_join(th[i], &res)) {
            return 2;
        }
        free(res);
    }
    return 0;
}