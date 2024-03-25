#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<errno.h>
#include<signal.h>
#include<wait.h>


void recycleChild(int arg)
{
    while(1)
    {
       int ret = waitpid(-1, NULL, WNOHANG);
       if(ret == -1)
       {// 所有子进程都回收了
        break;
       }
       else if(ret == 0)
       {
        break;
       }
       else if(ret > 0)
       {
        // 回收了子进程
        printf("子进程: %d 被回收\n", ret);
       }
    }
}

int main()
{
    // 注册信号捕捉
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = recycleChild;
    sigaction(SIGCHLD, &act, NULL);

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

    // 等待客户端连接
    while(1)
    {
        struct sockaddr_in client_addr;
        int len = sizeof(client_addr);
        int cfd = accept(lfd, (struct sockaddr*)&client_addr, &len);
        if(cfd == -1)
        {
            if(errno == EINTR)
            {
                continue;
            }
            perror("accept");
            exit(-1);
        }

        // 创建子进程与客户端通信
        pid_t pid = fork();
        if(pid == 0)
        {
            // 子进程
            // 获取客户端信息
            char client_ip[16];
            inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_ip, sizeof(client_ip));
            unsigned short client_port = ntohs(client_addr.sin_port);
            printf("client ip: %s, port: %d\n", client_ip, client_port);

            // 接受信息
            char recvBuf[1024] = {0};
            while(1)
            {
                int len = read(cfd, &recvBuf, sizeof(recvBuf));

                time_t cur_time;
                time(&cur_time);
                char* cur_t = ctime(&cur_time);
                write(cfd, cur_t, strlen(cur_t) + 1);

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
            close(cfd);
            exit(0);
        }
    }
    close(lfd);
    return 0;
}