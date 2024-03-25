#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main()
{
    int ret =  access("fifo1", F_OK);
    if(ret == -1)
    {
        printf("fifo not exist creat one\n");
        ret = mkfifo("test", 0664);
        if(ret == -1)
        {
            perror("mkfifo");
            exit(0);
        }
    }
    // 以只写打开管道
    int fd = open("test", O_WRONLY);
    if(fd == -1)
    {
        perror("open");
        exit(0);
    }
    for(int i = 0; i < 100; i++)
    {
        char buf[1024] = {0};
        sprintf(buf, "hello, %d\n", i);
        printf("writed data:%s", buf);
        write(fd, buf, strlen(buf));
        sleep(1);
    }
    close(fd);
    return 0;
}