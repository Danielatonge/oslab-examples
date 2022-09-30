#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int x = 2;

int main(void) {
    int pid = fork();
    if (pid == -1) {
        return 1;
    }
    if (pid == 0) {
        x += 5;
    }
    sleep(2);
    printf("Value of x: %d", x);
    printf("Hello from processes: PID - %d\n", getpid());
    if (pid != 0) {
        wait(NULL);
    }
    return 0;
}