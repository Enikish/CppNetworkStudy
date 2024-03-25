/*
    #include <sys/types.h>
    #include <sys/wait.h>

    pid_t wait(int *wstatus);
        功能:
            等待任意一个子进程结束， 如果任意一个子进程结束了， 此函数会回收子进程的id
        参数:
            int *wstatus
                进程退出时的状态信息， 传入的是一个int类型的地址，传出参数
        return:
            成功:
                返回被回收的子进程id
            失败:
                返回-1
    调用wait函数的进程会被挂起， 知道它的一个子进程退出或者收到一个不能被忽略的信号时才能被唤醒
    如果没有子进程了，函数立刻返回，返回-1；如果子进程都已经结束了， 也会立即返回-1

       
*/
#include <sys/types.h>
#include <sys/wait.h>
#include<unistd.h>
#include<stdio.h>
int main()
{
    pid_t pid;
    //生成五个子进程
    for(int i = 0; i < 5; ++i)
    {
        pid = fork();
        if(pid == 0)
        break;
    }
    if(pid > 0)
    {
        while(1){
            printf("parent pid = %d\n", getpid());

            int st;
            int ret = wait(&st);
            if(ret == -1)
            {
                break;
            }

            if(WIFEXITED(st))
            {
                //是否正常退出
                printf("status code while exit:%d\n", WEXITSTATUS(st));
            }
            else if(WIFSIGNALED(st))
            {
                printf("it's killed by %d signal\n", WTERMSIG(st));
            }
            printf("child die , pid = %d\n", ret);
            sleep(1);
        }
    }
    else if(pid == 0)
    {
        while(1)
        {
            printf("child pid = %d\n", getpid());
            sleep(1);
        }
    }
    return 0;
}