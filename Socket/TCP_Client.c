// TCP客户端
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    time_t cur_time;
    time(&cur_time);


    // 创建套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);


    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, "10.0.4.5", &server_addr.sin_addr.s_addr);
    server_addr.sin_port = htons(9999);
    int ret = connect(fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if(ret == -1)
    {
        perror("connect");
        exit(-1);
    }


    // 通信
    char recvbuf[1024];
    int len = read(fd, recvbuf, sizeof(recvbuf));
    if(len == -1)
    {
        perror("read");
        exit(-1);
    }
    else if(len >0){
        printf("recv client data: %s\n", recvbuf);
    }
    else if(len == 0)
    {// 表示客户端断开连接
        printf("server closed connect\n");
    }
    char* data = "hello i am clinet\n";
    write(fd, data, strlen(data));
    
    close(fd);
    return 0;
}
