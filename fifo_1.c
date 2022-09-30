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
    srand(time(NULL));

    for (int i = 0; i < 5; i++){
       arr[i] = rand() % 100;
    }
    
    int fd = open("sum", O_WRONLY);
    if (fd == -1) {
        return 1;
    }

    // We have opened the fifo 
    // for reading from another process
    // so we can write to it

    for (int i = 0; i < 5; i++){
        if(write(fd, &arr[i], sizeof(int)) == -1) {
            return 2;
        }
        printf("Wrote %d\n", arr[i]);
    }
    
    close(fd);
    return 0;
}