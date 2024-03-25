/**
 *      #include <pthread.h>

        int pthread_cancel(pthread_t thread);
 *          功能：
                取消线程(让线程终止)
                但是不是立马终止, 而是当子线程执行到一个取消点, 线程才会终止
                取消点:
                    系统规定好的系统调用
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

    pthread_cancel(tid);
    printf("tid: %ld, main thread id: %ld\n", tid, pthread_self());



    pthread_exit(tid);

    return 0;
}