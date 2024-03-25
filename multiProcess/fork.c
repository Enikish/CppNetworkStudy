/*
        #include <sys/types.h>
        #include <unistd.h>

        pid_t fork(void);
        作用:
            用于创建子进程
        return:
            fork()返回两次，一次是在父进程中，一次在子进程中
            在父进程中返回创建的子进程的ID
            在子进程中返回0
        如何区分父进程和子进程：
            通过fork()的返回值
        在父进程中返回-1， 表示子进程创建失败并设置errno为EAGAIN
        fork()之后，子进程的用户区数据和父进程一样。内核区也会拷贝过来，但是pid不一样

        fork()函数产生的进程是只有进行写操作时才会拷贝，在只读操作时是只读共享。
        读时共享，写时拷贝

        父子进程之间的关系
        区别：
            1. fork()函数的返回值不同
                父进程中: >0 返回子进程的ID
                子进程中: =0
            2. pcb中的一些数据
                当前进程的id pid
                当前进程的父进程的id ppid
        共同点：
            某些状态下: 子进程刚被创建出来，还没有执行任何读写操作
                - 用户区数据
                - 文件描述符表
        父子进程对变量是否共享:
            - 刚开始共享， 如果修改数据则不共享
            - 读时共享， 写时拷贝
        在gdb调试中可以用set follow-fork-mode [parent| child] 设置调试父进程或者子进程
        设置调试模式: set-detach-on-fork [on| off]
        默认为on, 表示调试当前进程的时候，其他的进程继续运行， 如果为off, 调试当前进程的时候其他进程被gdb挂起
        查看当前调试的进程: info inferiors
        切换当前调试的进程: inferior id
        使进程脱离GDB调试: detach inferiors id
*/
#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
int main()
{
    // 创建子进程
    pid_t pid = fork();

    if(pid > 0)
    {// 返回的是创建的子进程的ID， 当前是父进程
        printf("pid %d\n", pid);
        printf("i am parent, pid : %d, ppid : %d\n", getpid(), getppid());
    }else if(pid == 0)
    {// 当前是子进程
        printf("i am the child pid : %d, ppid : %d\n", getpid(), getppid());
    }
    for(int i = 0; i < 3; i++)
    {
        printf("i : %d  pid : %d\n", i, getpid());
        sleep(1);
    }
    return 0;
}