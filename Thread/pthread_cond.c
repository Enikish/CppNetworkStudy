/**
 *  条件变量类型:
 *      pthread_cond_t
 *  int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
 *  
 *  int pthread_cond_destroy(pthread_cond_t *cond);
 * 
 *  int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
 *      等待, 调用了该函数, 线程会阻塞
 * 
 *  int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex,
 *                               const struct timespec *restrict abstime);
 *      等待多长时间, 调用了这个函数, 线程会阻塞, 直到指定的时间结束     
 * 
 *  int pthread_cond_signal(pthread_cond_t *cond);
 *      唤醒一个或者多个等待的线程
 *  
 *  int pthread_cond_broadcast(pthread_cond_t *cond);
 *      唤醒所有的等待的线程
 * 
*/
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

struct Node{
    int num;
    struct Node* next;
};

// 头结点
struct Node* head = NULL;

pthread_cond_t cond;

pthread_mutex_t mutex;

void* producer(void* arg)
{
    // 创建新的节点加到链表中
    while(1)
    {
        pthread_mutex_lock(&mutex);
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000;
        printf("add node, num: %d, tid: %ld\n", newNode->num, pthread_self());

        // 只要生产了一个, 就通知消费者消费
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);
        usleep(100);
    }

    return NULL;
}

void* customer(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        struct Node* tmp = head;
        if(head != NULL)
        {
            head = head->next;
            printf("del node, num:%d, tid: %ld\n", tmp->num, pthread_self());
            free(tmp);
            pthread_mutex_unlock(&mutex);
            usleep(100);
        }
        else
        { // 没有数据
            // 当这个函数阻塞的时候， 会对互斥锁进行解锁, 当不阻塞时, 继续对互斥锁加锁
            pthread_cond_wait(&cond, &mutex);
        }
        
    }


    return NULL;
}

int main()
{
    pthread_t ptids[5], ctids[5];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

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
    pthread_cond_destroy(&cond);
    pthread_exit(NULL);

    return 0;
}