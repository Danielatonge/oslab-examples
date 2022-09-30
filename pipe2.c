#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
    int arr[] = {1, 2, 3, 4, 1, 2};
    int size = sizeof(arr)/sizeof(arr[0]);
    int start, end;
    int fd[2];
    // fd[0] - read end
    // fd[1] - write end
    if(pipe(fd) == -1) { 
        printf("Error creating pipe\n");
        return 1;
    };

    int id = fork();
    if (id == 0) {
        start = 0;
        end = start + size/2;
    } else {
        start = size/2;
        end = size;
    }

    int sum = 0;
    for (int i = start; i < end; i++){
        sum += arr[i];
    }

    printf("Calculated partial sum: %d\n", sum);
    
    if (id == 0){
        close(fd[0]);
        write(fd[1], &sum, sizeof(int));
        close(fd[1]);
    } else {
        close(fd[1]);
        int partial_sum;
        read(fd[0], &partial_sum, sizeof(int));
        close(fd[0]);
        printf("Total sum: %d\n", partial_sum + sum);
    }

    return 0;
}