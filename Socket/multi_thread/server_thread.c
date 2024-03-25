#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
#define max 128

struct sockInfo
{
    int fd; // 文件描述符
    pthread_t tid; // 线程号
    struct sockaddr_in addr; 
};

struct sockInfo sockInfos[max];

void* working(void* arg)
{
    struct sockInfo* pinfo = (struct sockInfo*)arg;
    // 子线程和客户端通信
    // 获取客户端信息
        char client_ip[16];
        inet_ntop(AF_INET, &pinfo->addr.sin_addr.s_addr, client_ip, sizeof(client_ip));
        unsigned short client_port = ntohs(pinfo->addr.sin_port);
        printf("client ip: %s, port: %d\n", client_ip, client_port);

        // 接受信息
        char recvBuf[1024] = {0};
        while(1)
        {
            int len = read(pinfo->fd, &recvBuf, sizeof(recvBuf));

            time_t cur_time;
            time(&cur_time);
            char* cur_t = ctime(&cur_time);
            write(pinfo->fd, cur_t, strlen(cur_t) + 1);

            if(len == -1)
            {
                perror("read");
                exit(-1);
            }
            else if(len > 0)
            {
                printf("recv buf: %s\n", recvBuf);
            }
            else if(len == 0){
                printf("client closed\n");
                break;
            }
            
        }
        close(pinfo->fd);

    return NULL;
}

int main()
{
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    if(lfd == -1)
    {
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(lfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(ret == -1)
    {
        perror("bind");
        exit(-1);
    }

    ret = listen(lfd, 128);
    if(ret == -1)
    {
        perror("listen");
        exit(-1);
    }

    //  初始化数据
    for(int i = 0; i < max; ++i)
    {
        bzero(&sockInfos[i], sizeof(sockInfos[i]));
        sockInfos[i].fd = -1;
        sockInfos[i].tid = -1;
    }

    // 循环等待客户端连接
    while(1)
    {
        struct sockaddr_in client_addr;
        int len = sizeof(client_addr);
        // 接受连接
        int cfd = accept(lfd, (struct sockaddr*)&client_addr, &len);

        // 创建子线程
        struct sockInfo* pinfo;
        for(int i = 0; i < max; ++i)
        {
            if(sockInfos[i].fd == -1)
            {
                pinfo = &sockInfos[i];
                break;
            }
            else if(i == max - 1)
            {
                sleep(1);
                i = 0;
            }
        }
        pinfo->fd = cfd;
        memcpy(&pinfo->addr, &client_addr, len);
        pthread_create(&pinfo->tid, NULL, working, pinfo);
        pthread_detach(pinfo->tid);
    }
    close(lfd);

    return 0;
}