/**
 *  读写锁类型: pthread_rwlock_t
 *  int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr);
 * 
 *  int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
 * 
 *  int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
 * 
 *  int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
 * 
 *  int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
 * 
 *  int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
 * 
 *  int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
 *  
 *  创建8个线程操作同一个全局变量
 *  3个线程不定时写, 5个线程不定时读
*/


#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

int num = 1;
pthread_rwlock_t rw;

void* writeNum(void* arg)
{
    while(1)
    {
        pthread_rwlock_wrlock(&rw);
        printf("write, tid: %ld, num: %d\n", pthread_self(), num);
        ++num;
        pthread_rwlock_unlock(&rw);
        sleep(1);
    }
    return NULL;
}

void* readNum(void* arg)
{
    while(1)
    {
        pthread_rwlock_rdlock(&rw);
        printf("read tid: %ld, num: %d\n", pthread_self(), num);
        pthread_rwlock_unlock(&rw);
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_rwlock_init(&rw, NULL);

    pthread_t wtids[3], rtids[5];
    for(int i = 0; i < 3;++i)
    {
        pthread_create(&wtids[i], NULL, writeNum, NULL);
    }

    printf("==========\n");

    for(int i = 0; i < 5; ++i)
    {
        pthread_create(&rtids[i], NULL, readNum, NULL);
    }

    for(int i = 0; i < 5; ++i)
    {
        pthread_detach(rtids[i]);
    }

    for(int i = 0; i < 3; ++i)
    {
        pthread_detach(wtids[i]);   
    }

    pthread_exit(NULL);
    pthread_rwlock_destroy(&rw);
    return 0;
}