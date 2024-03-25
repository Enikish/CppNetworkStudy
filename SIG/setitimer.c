/**
 *      #include <sys/time.h>

        int getitimer(int which, struct itimerval *curr_value);
        int setitimer(int which, const struct itimerval *new_value,
                     struct itimerval *old_value);
            功能:
                设置定时器, 可以替代alarm函数. 精度是us, 可以实现周期性的定时
            参数：
                which:
                    定时器以什么时间计时:
                    ITIMER_REAL:
                        真实时间, 时间到达, 发送SIGALARM
                    ITIMER_VIRTUAL:
                        用户时间, 时间到达, 发送SIGVTALARM
                    ITIMER_PROF:
                        以该进程在用户态和内核态下所消耗的时间来计算, 时间到达, 发送SIGPROF
                new_value:
                    设置定时器的属性
                    struct itimerval {
                        struct timeval it_interval;  Interval for periodic timer 
                        struct timeval it_value;     Time until next expiration 
                    };

                    struct timeval {
                        time_t      tv_sec;          seconds 
                        suseconds_t tv_usec;         microseconds 
                    };
                old_value:
                    记录上一次的定时器的参数
            return:
                成功： 0
                失败: -1
*/
#include<sys/time.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    struct itimerval new_value;

    //设置间隔的时间
    new_value.it_interval.tv_sec = 1;
    new_value.it_interval.tv_usec = 0;

    //设置第一次发送延迟的时间
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;

   int ret =  setitimer(ITIMER_REAL, &new_value, NULL);
    if(ret == -1)
    {
        perror("setitimer");
        exit(0);
    }
    getchar();
    return 0;
}