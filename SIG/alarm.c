/**
 *      #include <unistd.h>

        unsigned int alarm(unsigned int seconds);
            功能：
                设置定时器。函数调用, 开始倒计时, 当倒计时为0时, 函数会给当前进程发送一个SIGALARM信号
            参数：
                seconds:
                    倒计时的时长, 单位是秒。 如果参数为0， 定时器无效
                    取消一个定时器, 通过alarm(0)
            return:
                之前没有定时器, 返回0
                之前有定时器, 返回之前的定时器剩余的时间
        
        -SIGALARM:
            默认终止当前的进程, 每一个进程都有且只有唯一的一个定时器
        alarm(10); 返回 0
        过了一秒
        alarm(5); 返回9
        alarm()是不阻塞的
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
   int sec =  alarm(5);
   printf("sec = %d\n", sec); // 0
   sleep(2);
   sec = alarm(3); // 非阻塞
   printf("sec = %d\n", sec); // 3
   while(1)
   {

   }
    return 0;
}