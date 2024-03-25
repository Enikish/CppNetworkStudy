#include<stdio.h>
#include<pthread.h>



void* sellticket(void* arg)
{
    int tickets = 100;
    while(tickets > 0)
    {
        printf("%ld selling No.%d ticker", pthread_self(), tickets);
        --tickets;
    }

}


int main()
{
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


    return 0;
}