#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/select.h>

int main()
{
    // 创建socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr;
    saddr.sin_port = htons(9999);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;

    // 绑定
    bind(lfd, (struct sockaddr*)&saddr, sizeof(saddr));

    // 监听
    listen(lfd, 8);

    // 创建一个fd_set集合, 存放的是需要检测的文件描述符
    fd_set rdset, tmp;
    FD_ZERO(&rdset);
    FD_SET(lfd, &rdset);

    int maxfd = lfd;
    while(1)
    {
        tmp = rdset;
        // 调用Select函数, 让内核检测哪些文件描述符有更新
        int ret = select(maxfd + 1, &tmp, NULL, NULL, NULL);
        if(ret == -1)
        {
            perror("select");
            exit(-1);
        }
        else if(ret == 0)
        {
            continue;
        }
        else if(ret > 0)
        {
            // 检测到了有文件描述符发生改变
            if(FD_ISSET(lfd, &tmp))
            {
                // 表示有新的客户端连接
                struct sockaddr_in client_addr;
                int len = sizeof(client_addr);
                int cfd = accept(lfd, (struct sockaddr*)&client_addr, &len);

                // 将新的文件描述符加入集合当中
                FD_SET(cfd, &rdset);

                // 更新最大的文件描述符
                maxfd = maxfd > cfd ? maxfd : cfd;
            }
            for(int i = lfd + 1; i <= maxfd; ++i)
            {
                if(FD_ISSET(i, &tmp))
                {
                    // 说明这个文件描述符对应的客户端发来数据
                    char buf[1024] = {0};
                    int len = read(i, buf, sizeof(buf));
                    if(len == -1)
                    {
                        perror("read");
                        exit(-1);
                    }
                    else if(len == 0)
                    {
                        printf("client closed\n");
                        close(i);
                        FD_CLR(i, &rdset);
                    }
                    else if(len > 0)
                    {
                        printf("read data: %s\n", buf);
                        write(i, buf, strlen(buf) + 1);
                    }
                }
            }
        }
    }
    close(lfd);
    return 0;
}