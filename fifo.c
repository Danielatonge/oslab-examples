#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

int main() {
    mkfifo("timolai", 0777);

    printf("Opening...\n");
    int fd = open("timolai", O_RDWR);
    if (fd == -1) {
        return 3;
    }


    printf("Opened\n");


    int x = 100;
    if(write(fd, &x, sizeof(x)) == -1) {
        return 2;
    }
    printf("Written\n");

    close(fd);
    printf("Closed\n");
    return 0;
}