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

    // 设置广播属性
    int op = 1;
    setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &op, sizeof(op));

    // 创建广播地址
    struct sockaddr_in cliaddr;
    struct sockaddr_in server_addr;
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(9999);
    inet_pton(AF_INET, "10.0.4.255", &cliaddr.sin_addr.s_addr);

    // 通信
    int num = 0;
    while(1)
    {
        char buf[1024] = {0};
        sprintf(buf, "hello %d\n", num++);

        // 发送数据
        sendto(fd, buf, strlen(buf) + 1, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
        printf("data: %s\n", buf);
        sleep(1);
    }
    
    close(fd);

    return 0;
}