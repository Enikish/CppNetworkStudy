/**
 *      #include <sys/types.h>
        #include <sys/socket.h>

        ssize_t send(int sockfd, const void *buf, size_t len, int flags);
            用于TCP

        ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                        const struct sockaddr *dest_addr, socklen_t addrlen);
            参数:
                sockfd:
                    通信的fd
                buf:
                    要发送的数据
                len:
                    发送数据的长度
                flags: 0
                dest_addr:
                    通信的另外一端地址信息
                addrlen:
                    地址的内存大小
            return:
                成功:
                    返回发送的数据长度
                失败:
                    -1
        
        #include <sys/types.h>
        #include <sys/socket.h>

        ssize_t recv(int sockfd, void *buf, size_t len, int flags);

        ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                            struct sockaddr *src_addr, socklen_t *addrlen);
            参数:
                sockfd:
                    通信的fd
                buf:
                    接收数据的数组
                len:
                    数组的大小
                flags: 0
                src_addr:
                    用来保存另一端的地址信息, 不需要可以保存为NULL
                addrlen:
                    地址内存大小

*/
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
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bind(fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 通信
    while(1)
    {
        char buf[1024] = {0};
        char ipbuf[16];
        struct sockaddr_in client_addr;
        int len = sizeof(client_addr); 
        int num = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, &len);
        printf("client ip:%s, port:%d\n",
            inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ipbuf, sizeof(ipbuf)),
            ntohs(client_addr.sin_port));
        printf("recv buf:%s\n", buf);

        // 发送数据
        sendto(fd, buf, strlen(buf) + 1, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
    }
    
    close(fd);

    return 0;
}