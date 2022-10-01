#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>
#include<time.h>

int main() {
    char arr[500];
    while(1) {
        int fd = open("sum", O_RDONLY);
        if (fd == -1) {
            return 1;
        }

        // We have opened the fifo 
        // for writing from another process
        // so we can read from it

        if(read(fd, arr, strlen(arr)+ 1) == -1) {
            return 2;
        }
        printf("Received %s\n", arr);
        
        close(fd);
    }
    return 0;
}