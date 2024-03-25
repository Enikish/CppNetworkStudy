/*
    实现 ps aux | grep xx 父子进程间通信
    子进程: ps aux, 子进程结束后， 将数据发送给父进程
    父进程: 获取数据， 过滤

    pipe()
    execlp()
    子进程将标准数据重定向到管道的写端， dup2
*/

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wait.h>
int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1)
    {
        perror("pipe");
        exit(0);
    }
    pid_t pid = fork();
    if(pid > 0)
    {/**
        父进程
        从管道中获取
        过滤数据输出*/
        close(fd[1]);
        char buf[1024] = {0};
        int len = -1;
        // 将所有数据读出
        while(len = read(fd[0], buf, sizeof(buf) - 1) > 0)
        {
            printf("%s",buf);
            memset(buf, 0, 1024);
        }
        wait(NULL);
    }
    else if( pid == 0)
    {
        close(fd[0]);
        /*
        子进程
        文件描述符的重定向 stdout_fileno -> fd[1]
        */
       dup2(fd[1], STDOUT_FILENO);

       execlp("ps", "ps", "aux", NULL);
       perror("exec");
       exit(0);
    }
    else 
    {
        perror("fork");
        exit(0);
    }

    return 0;
}