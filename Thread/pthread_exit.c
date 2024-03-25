/**
 *#     include <pthread.h>

        void pthread_exit(void *retval);
            功能：
                终止一个线程, 在哪个线程中调用, 就表示终止那个线程
            参数:
                retval:
                    需要传递一个指针, 作为一个返回值, 可以在pthread_join()中获取到
        pthread_t pthread_self(void);
            功能：
                获取当先线程的线程ID

        int pthread_equal(pthread_t t1, pthread_t t2);
            功能:
                比较两个线程ID是否相等
            不同的操作系统对于pthread_t的实现不一样, 有使用结构体实现的, 此时用 == 符号就会报错
*/
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void* callback(void* arg)
{
    printf("child thread id: %ld\n", pthread_self());
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

    printf("tid: %ld, main thread id: %ld\n", tid, pthread_self());
    // 让主线程退出, 当主线程退出时, 不会影响其他正常运行的线程
    pthread_exit(NULL);

    return 0;
}