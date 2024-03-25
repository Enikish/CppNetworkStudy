/**
 *      #include <pthread.h>

        int pthread_attr_init(pthread_attr_t *attr);
            初始化线程属性变量

        int pthread_attr_destroy(pthread_attr_t *attr);
            释放线程属性资源

        int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
            获取线程分离的状态属性

        int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
            设置线程分离的状态属性
 * 
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

void* callback(void* arg)
{
    printf("child thread id: %ld\n", pthread_self());
    return NULL;
}

int main()
{
    pthread_attr_t attr;
    // 初始化
    pthread_attr_init(&attr);
    // 设置
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_t tid;

    int ret = pthread_create(&tid, &attr, callback, NULL);
    if(ret != 0)
    {
        char* errstr = strerror(ret);
        printf("error: %s\n",errstr);
    }

    printf("tid: %ld, main thread id: %ld\n", tid, pthread_self());

    // 释放线程属性资源
    pthread_attr_destroy(&attr);

    pthread_exit(tid);

    return 0;
}