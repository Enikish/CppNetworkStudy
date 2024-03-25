#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

int main()
{
    int shmid = shmget(100, 0, IPC_CREAT);

    void* ptr = shmat(shmid, NULL, 0);

    printf("%s\n", (char*)ptr);
    printf("press any key\n");
    getchar();

    // 解除关联
    shmdt(shmid);

    // 删除共享内存
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}