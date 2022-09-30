#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
int x = 2;

void * func() {
    sleep(2);
    x += 7;
    printf("Value of x: %d\n", x);
}
void * func2() {
    sleep(2);
    printf("Value of x: %d\n", x);
}
int main(void) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, &func, NULL);
    pthread_create(&t2, NULL, &func2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Good\n");
    return 0;
}