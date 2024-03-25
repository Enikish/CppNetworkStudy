/**
 *      对自定义的信号集操作
 *      #include <signal.h>

        int sigemptyset(sigset_t *set);
            功能:
                清空信号集中的数据, 将信号集中的所有标志位置0
            参数:
                set, 传出参数, 需要操作的信号集
            return:
                成功: 0
                失败：-1

        int sigfillset(sigset_t *set);
            功能:
                将信号集中的所有标志位置1
            参数:
                set, 传出参数, 需要操作的信号集
            return:
                成功: 0
                失败：-1

        int sigaddset(sigset_t *set, int signum);
            功能:
                设置信号集中的某一个信号对应的标志位为1， 表示阻塞该信号
            参数:
                set:
                    传出参数, 需要操作的信号集
                signum：
                    需要设置阻塞的那个信号
            return:
                成功: 0
                失败：-1

        int sigdelset(sigset_t *set, int signum);
            功能:
                清空信号集中的数据, 将信号集中的所有标志位置0
            参数:
                set:
                    传出参数, 需要操作的信号集
                signum：
                    需要设置不阻塞的那个信号
            return:
                成功: 0
                失败：-1
        int sigismember(const sigset_t *set, int signum);
            功能:
                判断某个信号是否阻塞
            参数：
                set：
                    需要操作的信号集
                signum:
                    需要判断的信号
            return:
                1:
                    signum被阻塞
                0：
                    signum不阻塞
                -1:
                    调用失败
*/
#include <signal.h>
#include<stdio.h>


int main()
{
    sigset_t set; 
    // 清空信号集
    sigemptyset(&set);
    
   int ret =  sigismember(&set, SIGINT);
   if(ret == 0)
   {
    printf("SIGINT nonblock\n");
   }
   else if(ret == 1)
   {
    printf("SIGINT blocked\n");
   }
    //将信号添加到信号集中
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    ret =  sigismember(&set, SIGINT);
   if(ret == 0)
   {
    printf("SIGINT nonblock\n");
   }
   else if(ret == 1)
   {
    printf("SIGINT blocked\n");
   }
    //删除信号
   sigdelset(&set, SIGQUIT);
   ret =  sigismember(&set, SIGQUIT);
   if(ret == 0)
   {
    printf("SIGQUIT nonblock\n");
   }
   else if(ret == 1)
   {
    printf("SIGQUIT blocked\n");
   }
    return 0;
}