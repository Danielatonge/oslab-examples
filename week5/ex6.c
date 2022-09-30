#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

void * roll_dice() {
    int value = (rand() % 6) + 1;
    int * result = malloc(sizeof(int ));
    *result = value;
    printf("%d\n", value);

    return (void *)result;
}

int main(void) {
    int * res;
    pthread_t th;
    srand(time(NULL));
  
    if (pthread_create(&th, NULL, &roll_dice, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    if(pthread_join(th, &res)) {
        return 2;
    }

    printf("Result: %d\n", *res);
    free(res);
    return 0;
}