/**
 *      #include <sys/types.h>
        #include <signal.h>

        int kill(pid_t pid, int sig);
        功能:
            给任何进程或者进程组pid 发送某个信号sig
        参数:
            pid:
                > 0:
                    将信号发送给指定的进程
                = 0:
                    将信号发送给当前的进程组
                = -1:
                    将信号发送给每一个有权限接受这个信号的进程
                < -1:
                    这个pid = 某个进程组的ID取反
                需要发送给的进程的id
            sig:
                需要发送的信号的编号或宏值, 0 表示不发送任何信号
        kill(getpid(), 9);
        kill(getppid(), 9);

        int raise(int sig);
            功能:
                给当前进程发送信号
            参数:
                sig:
                    要发送的信号
            return:
                成功: 0
                失败: 非 0
        kill(getpid(), sig);

        void abort(void);
            功能：
                发送SIGABRT给当前的进程, 杀死当前进程
                kill(getpid(), SIGABRT);
*/
#include<stdio.h>
#include<sys/types.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    pid_t pid = fork();
    if(pid == 0)
    {
        int i = 0;
        for(i = 0; i < 5; ++i)
        {
            printf("child process\n");
            sleep(1);
        }
    }
    else if(pid > 0)
    {
        printf("parent process\n");
        sleep(2);
        printf("kill child process now\n");
        kill(pid, SIGINT);
    }

 return 0;   
}