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
        printf(">> ");
        fgets(arr, 500, stdin);
        
        int fd = open("sum", O_WRONLY);
        if (fd == -1) {
            return 1;
        }

        // We have opened the fifo 
        // for reading from another process
        // so we can write to it
        for (int i = 0; i < 2; i++){
            if((write(fd, arr, strlen(arr) + 1)) == -1) {
                return 2;
            }
            printf("Wrote %s\n", arr);
        }
        
        close(fd);
    }
    return 0;
}