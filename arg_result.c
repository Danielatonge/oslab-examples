#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

int prime[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void * unique(void *arg) {
    int index = *(int *)arg;
    int sum = 0;
    for (int j = 0; j < index + 5; j++){
        sum += prime[index + j];
    }
    *(int *)arg = sum;
    return arg;
}

int main(void) {
    int * res;
    pthread_t th[10];
    srand(time(NULL)); 
    for (int i = 0; i < 2; i++) {
        int * iptr = malloc(sizeof(int));
        *iptr = i*5;
        if (pthread_create(&th[i], NULL, &unique, iptr)) {
            perror("Failed to create thread");
            return 1;
        }
    }
    
    int globalsum = 0;
    for (int i = 0; i < 2; i++) {
        if(pthread_join(th[i], (void **)&res)) {
            return 2;
        }
        globalsum += *res;
        free(res);
    }
    printf("Sum: %d", globalsum);
    return 0;
}