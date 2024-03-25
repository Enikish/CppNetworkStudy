// TCP实现服务器
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
    int lfd = socket(AF_INET, SOCK_STREAM, 0);

    // 绑定
    struct sockaddr_in saddr;
    inet_pton(AF_INET, "10.0.4.5", (void*)&saddr.sin_addr.s_addr);
    saddr.sin_family = PF_INET;
    saddr.sin_port = htons(9999);
    bind(lfd, (struct sockaddr*)&saddr,  sizeof(saddr));

    
    // 监听
    listen(lfd, 8);

    // 接受客户端的连接
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int cfd = accept(lfd, (struct sockaddr*)&client_addr, &len);
    if(cfd == -1)
    {
        perror("accept");
        exit(-1);
    }

    // 输出客户端的信息
    char client_ip[16];
    inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_ip, sizeof(client_ip));
    unsigned short client_port = ntohs(client_addr.sin_port);
    printf("client ip is:%s, port is %d\n", client_ip, client_port);

    // 通信
    // 获取客户端的数据
    char recvbuf[1024];
    int num = read(cfd, recvbuf, sizeof(recvbuf));
    if(num == -1)
    {
        perror("read");
        exit(-1);
    }
    else if(num >0){
        printf("recv client data: %s\n", recvbuf);
    }
    else if(num == 0)
    {// 表示客户端断开连接
        printf("client closed connect\n");
    }

    // 给客户端发送数据
    char * data = "hello i am server";
    char* t = ctime(&cur_time);
    write(cfd, data, strlen(data));
    write(cfd, t, strlen(t));

    // 关闭文件描述符
    close(cfd);
    close(lfd);
    return 0;
}