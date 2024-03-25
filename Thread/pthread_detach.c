/**
 *      #include <pthread.h>

        int pthread_detach(pthread_t thread);
            功能：
                分离一个线程
                被分离的线程在终止的时候会自动释放资源
                1. 不能多次分离同一线程, 会造成未定义行为
                2. 不能连接一个已经分离的线程, 如果连接已分离线程, 会报错
            参数:
                成功： 0
                失败: 返回错误号
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
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, callback, NULL);
    if(ret != 0)
    {
        char* errstr = strerror(ret);
        printf("error: %s\n",errstr);
    }

    printf("tid: %ld, main thread id: %ld\n", tid, pthread_self());

    // 设置子线程分离
    pthread_detach(tid);

    pthread_exit(tid);

    return 0;
}