#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
// 子进程发送数据给父进程， 父进程读取到数据输出
/**
 * 设置管道非阻塞
 * int flags = fcntl(fd[0], F_GETFL); //获取原来的flag
 * flags |= O_NONBLOCK; // 修改flag的值
 * fcntl(fd[0], F_SETFL, flags);// 设置新的flag
*/
int main()
{

// 在fork之前创建管道
    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret == -1)
    {
        perror("pipe");
        exit(0);
    }
    // 创建子进程
    pid_t pid = fork();
    if(pid > 0)
    {
        //从管道的读取端读取数据
        printf("i am parent process, pid = %d", getpid());
        char buf[1024] = {0};
        while(1)
        {
            int len = read(pipefd[0], buf, sizeof(buf));
            printf("parent recv: %s, pid = %d\n", buf, getpid()); 
        }
    }
    else if (pid == 0)
    { // 子进程 
        printf("i am child process, pid = %d", getpid());
        
        while(1)
        {
            // 向管道中写入数据
            char* str = "hello i am child";
            write(pipefd[1], str, strlen(str)); 
            sleep(1);
        }
    }

return 0;
}