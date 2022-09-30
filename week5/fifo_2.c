#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>
#include<time.h>

int main() {
    int arr[5];
    
    int fd = open("sum", O_RDONLY);
    if (fd == -1) {
        return 1;
    }

    // We have opened the fifo 
    // for writing from another process
    // so we can read from it

    for (int i = 0; i < 5; i++){
        if(read(fd, &arr[i], sizeof(int)) == -1) {
            return 2;
        }
        printf("Received %d\n", arr[i]);
    }

    int sum = 0;
    for(int i = 0; i < 5; i++) {
        sum += arr[i];
    }
    printf("Result of sum: %d\n", sum);
    
    close(fd);
    return 0;
}