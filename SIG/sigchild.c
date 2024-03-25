/**
 * SIGCHILD信号产生的条件：
 *  1. 子进程结束了
 *  2. 子进程暂停了
 *  3. 子进程被唤醒
 *  都会给父进程发送该信号， 父进程默认忽略该信号
 * 
 * 使用SIGCHILD信号解决僵尸进程
 * 
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<signal.h>
#include<sys/wait.h>

void Fun(int num)
{
    printf("got %d signal\n", num);
    // 回收PCB
    // wait(NULL);
    while(1)
    {
        int ret = waitpid(-1, NULL, WNOHANG);
        if(ret > 0)
        {
            printf("child die pid = %d\n", ret);
        }
        else if(ret == 0)
        {
            break;
        }
        else if(ret == -1)
        {
            break;
        }
    }
}

int main()
{

    // 提前设置好阻塞信号集, 阻塞SIGCHLD， 因为有可能子进程很快结束， 父进程还没有注册
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);


    pid_t pid;
    for(int i = 0; i < 20; ++i)
    {
        pid = fork();
        if(pid == 0)
        {
            break;
        }
    }
    if(pid > 0)
    {

        //捕捉子进程死亡时发送的SIGCHILD信号
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = Fun;
        sigemptyset(&act.sa_mask);

        sigaction(SIGCHLD, &act, NULL);
        // 注册完信号捕捉以后, 解除阻塞
        sigprocmask(SIG_UNBLOCK, &set, NULL);
        while(1)
        {
            printf("parent process pid = %dn", getpid());
            sleep(2);
        }
    }
    else if(pid == 0)
    {
        printf("child process pid = %d\n", getpid());
    }

    return 0;
}