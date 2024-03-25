/**
 *      #include <semaphore.h>

        int sem_init(sem_t *sem, int pshared, unsigned int value);
            初始化信号量
            参数:
                sem:    
                    信号量变量的地址
                pshared:
                    0: 用在线程间
                    非0: 用在进程间
                value:
                    信号量中的值

        int sem_wait(sem_t *sem);
            对信号量加锁, 调用一次使信号量的值-1 , 如果值为0, 就阻塞

        int sem_trywait(sem_t *sem);

        int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);


        int sem_post(sem_t *sem);
            对信号量解锁, 调用一次信号量的值 +1

        int sem_getvalue(sem_t *sem, int *sval);

        int sem_destroy(sem_t *sem);
 * 
*/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>

struct Node{
    int num;
    struct Node* next;
};

// 头结点
struct Node* head = NULL;

pthread_mutex_t mutex;

sem_t csem;
sem_t psem;

void* producer(void* arg)
{
    // 创建新的节点加到链表中
    while(1)
    {
        sem_wait(&psem);
        pthread_mutex_lock(&mutex);
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000;
        printf("add node, num: %d, tid: %ld\n", newNode->num, pthread_self());
        pthread_mutex_unlock(&mutex);
        sem_post(&csem);
    }

    return NULL;
}

void* customer(void* arg)
{
    while(1)
    {
        sem_wait(&csem);
        pthread_mutex_lock(&mutex);
        struct Node* tmp = head;

        head = head->next;
        printf("del node, num:%d, tid: %ld\n", tmp->num, pthread_self());

        free(tmp);
        pthread_mutex_unlock(&mutex);
        sem_post(&psem);
    }


    return NULL;
}

int main()
{
    pthread_t ptids[5], ctids[5];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&psem, 0, 8);
    sem_init(&csem, 0, 0);

    for(int i = 0; i < 5; ++i)
    {
        pthread_create(&ptids[i], NULL, producer, NULL);
        pthread_create(&ctids[i], NULL, customer, NULL);
    }

    for(int i = 0; i < 5; ++i)
    {
        pthread_detach(ptids[i]);
        pthread_detach(ctids[i]);
    }

    while(1)
    {
        sleep(10);
    }

    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);

    return 0;
}