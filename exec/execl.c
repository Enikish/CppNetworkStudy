/*
        #include <unistd.h>

       extern char **environ;

       int execl(const char *pathname, const char *arg, ...
                       /* (char  *) NULL *//*);
            参数:
                pathname:
                 需要执行的文件的路径或名称，最好使用绝对路径
                arg:
                 是执行可执行文件需要的参数列表
                 第一个参数一般没有作用，为了方便一般是执行文件的名称
                 从第二个参数往后，是程序执行所需要的参数列表
                 参数最后需要以null结束
            return:
                只有出错时返回-1并设置errno
                如果成功则没有返回
       
       int execle(const char *pathname, const char *arg, ...
                       /*, (char *) NULL, char *const envp[] *//*);
       int execv(const char *pathname, char *const argv[]);
       int execvp(const char *file, char *const argv[]);
       int execvpe(const char *file, char *const argv[],
                       char *const envp[]);
*/
#include <unistd.h>
#include<stdio.h>
int main()
{
    //创建一个子进程， 在子进程中执行exec函数族中的函数
    pid_t pid = fork();
    if(pid > 0)
    {
        printf("i am parent, pid %d\n", getpid());
        sleep(1);
    }
    else if(pid == 0)
    {
        execl("hello","hello",NULL);
        printf("im child");
    }
    return 0;
}