/**
 *  生产者消费者模型
 *  生产者
 *  消费者
 *  容器
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
        pthread_mutex_unlock(&mutex);
        usleep(100);
    }

    return NULL;
}

void* customer(void* arg)
{
    while(1)
    {
        struct Node* tmp = head;

        head = head->next;
        printf("del node, num:%d, tid: %ld\n", tmp->num, pthread_self());
        free(tmp);
        usleep(100);
    }


    return NULL;
}

int main()
{
    pthread_t ptids[5], ctids[5];

    pthread_mutex_init(&mutex, NULL);

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


    pthread_exit(NULL);

    return 0;
}

