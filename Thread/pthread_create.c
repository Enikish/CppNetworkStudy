/**
 *  一般情况下, main函数所在的线程称为主线程, 其余创建的线程称为子线程
 *  程序中默认只有一个进程, fork()调用
 *  程序中默认只有一个线程, pthread_create()函数调用
 *       #include <pthread.h>

        int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                        void *(*start_routine) (void *), void *arg);
            功能:
                创建一个子线程 
            参数:
                thread:
                    传出参数, 线程创建成功后子线程的线程id写到该线程中
                attr:
                    设置线程的属性. 一般使用默认值, 传递NULL
                start_routine:
                    函数指针, 这个函数时子线程需要处理的逻辑代码
                arg:
                    给第三个参数使用, 传参
            return:
                成功: 0
                失败: 返回错误号, 和errno不一样
                获取错误号的信息: char* strerror(int errnum);
 * 
*/
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void* callback(void* arg)
{
    printf("child thread...\n");
    return NULL;
}

int main()
{
    pthread_t tid;
    // 创建子线程
    int ret = pthread_create(&tid, NULL, callback, NULL);
    if(ret != 0)
    {
        char* errstr = strerror(ret);
        printf("%s\n", errstr);
    }

    for(int i = 0; i < 5; ++i)
    {
        printf("%d\n", i);
    }

    return 0;
}