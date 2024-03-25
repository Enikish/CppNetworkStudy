#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main()
{
    // 创建socket
    int fd = socket(PF_INET, SOCK_DGRAM, 0);
    if(fd == -1)
    {
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    inet_pton(AF_INET, "10.0.4.5", &server_addr.sin_addr.s_addr);
    // 通信
    int num = 0;
    while(1)
    {
        char sendbuf[128];
        sprintf(sendbuf, "hello i am client%d\n", num++);

        // 发送数据
        sendto(fd, sendbuf, strlen(sendbuf) + 1, 0, (struct sockaddr*)&server_addr, sizeof(sendbuf));

        int num = recvfrom(fd, sendbuf, sizeof(sendbuf), 0, NULL, NULL);
        
        printf("recv buf:%s\n", sendbuf);
        sleep(1);
    }
    
    close(fd);

    return 0;
}