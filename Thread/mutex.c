/**
 *      int pthread_mutex_init (pthread_mutex_t *__mutex,
                const pthread_mutexattr_t *__mutexattr)
            功能: 
                初始化互斥量
            参数：
                mutex:
                    需要初始化的互斥量变量
                attr:
                    互斥量相关的属性
            restrict:
                C语言修饰符, 被修饰的指针, 不能由另外一个指针进行操作
        int pthread_mutex_destroy (pthread_mutex_t *__mutex)
            功能:
                释放互斥量的资源

        int pthread_mutex_trylock (pthread_mutex_t *__mutex)
            功能:
                尝试加锁, 如果加锁失败, 不会失败, 会直接返回
        int pthread_mutex_lock (pthread_mutex_t *__mutex)
            功能：
                加锁, 阻塞的, 如果有一个线程加锁, 其他线程只能阻塞等待
        int pthread_mutex_unlock (pthread_mutex_t *__mutex)
            功能:
                解锁
 * 
*/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
int tickets = 100;

pthread_mutex_t mutex;



void* sellticket(void* arg)
{
    // 每个线程获得互斥资源时加锁, 在该此操作完成后释放互斥资源    
    while(1)
    {
    // 加锁
    pthread_mutex_lock(&mutex);

    if(tickets > 0)
        {
            printf("%ld selling No.%d ticket\n", pthread_self(), tickets);
            --tickets;
            
        }
    else
    {
        // 解锁
        pthread_mutex_unlock(&mutex);
        break;
    }

    // 解锁
    pthread_mutex_unlock(&mutex);
    sleep(0.5);
    }
}


int main()
{

    //初始化互斥量
    pthread_mutex_init(&mutex, NULL);

    // 创建3个子线程
    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, sellticket, NULL);
    pthread_create(&tid2, NULL, sellticket, NULL);
    pthread_create(&tid3, NULL, sellticket, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    // pthread_detach(tid1);
    // pthread_detach(tid2);
    // pthread_detach(tid3);

    // 退出主线程
    pthread_exit(NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}