#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
    int fd[2];
    // fd[0] - read end
    // fd[1] - write end
    if(pipe(fd) == -1) { 
        printf("Error");
        return 1;
    };

    int id = fork();
    if (id == 0) {
        close(fd[0]);
        int x;
        printf("Input a number: ");
        scanf("%d", &x);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    } else {
        close(fd[1]);
        int y;
        read(fd[0], &y, sizeof(int));
        close(fd[0]);
        printf("Got from child process: %d\n", y);
    }

// Important: Don't forget error checking
    return 0;
}