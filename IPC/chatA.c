#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>


int main()
{
    // 判断有名管道是否存在
    int ret = access("fifo1", F_OK);
    if(ret == -1)
    {
       ret = mkfifo("fifo1", 0664);
       if(ret == -1)
       {
        perror("fifo");
        exit(-1);
       }
    }
    ret = access("fifo2", F_OK);
    if(ret == -1)
    {
       ret = mkfifo("fifo2", 0664);
       if(ret == -1)
       {
        perror("fifo");
        exit(-1);
       }
    }
    // 以只写的方式打开管道fifo1
    int fdw = open("fifo1", O_WRONLY);
    if(fdw == -1)
    {
        perror("open fifo1");
        exit(-1);
    }
    printf("successfully opened fifo1\n");

    //以只读的方式打开管道2
    int fdr = open("fifo2", O_RDONLY);
    if(fdr == -1)
    {
        perror("open fifo2");
        exit(-1);
    }
    printf("successfully opened fifo2\n");
    
    pid_t pid = fork();

    char buf[128];
    while(1)
    {
        if(pid > 0)
        {
            memset(buf, 0, 128);
            //获取标准输入
            fgets(buf, 128, stdin);
            //写数据
            ret = write(fdw, buf, strlen(buf));
            if(ret == -1)
            {
                perror("write");
                exit(-1);
            }
        }
        else if(pid == 0)
        {
            //读数据
            memset(buf, 0, 128);
            ret = read(fdr, buf, 128);
            if(ret <= 0)
            {
                perror("read");
                break;
            }
            printf("buf:%s\n", buf);
        }
    }
    close(fdw);
    close(fdr);
    return 0;
}