/****
 *      #include <pthread.h>

        int pthread_join(pthread_t thread, void **retval);
            功能:
                和一个已经终止的线程进行连接
                回收子线程的资源
                这个函数是阻塞函数, 调用一次只能回收一个子线程
                一般在主线程中使用
            参数:
                thread:
                    需要回收的子线程的id
                retval:
                    接收子线程退出时的返回值
            return:
                成功: 0
                失败: 返回非零的错误号
 * 
 * 
 * 
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
    //
    ret = pthread_join(tid, NULL);
    if(ret != 0)
    {
        char* errstr = strerror(ret);
        printf("%s\n", errstr);
    }

    printf("回收子线程成功\n");

    // 让主线程退出, 当主线程退出时, 不会影响其他正常运行的线程
    pthread_exit(NULL);

    return 0;
}