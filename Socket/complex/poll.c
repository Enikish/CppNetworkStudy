/**
 *      #include <poll.h>

        int poll(struct pollfd *fds, nfds_t nfds, int timeout);
            参数:
                fds:
                    是一个struct pollfd 结构体数组, 这是一个需要检测的文件描述符的集合
                nfds:
                    这个是第一个参数数组最后一个有效元素的下标 + 1
                timeout:
                    阻塞时长:
                        0: 不阻塞
                        -1: 阻塞, 当检测到需要检测的文件描述符有变化, 就接触阻塞
                        >0: 阻塞时长
            return:
                成功: >0, n个文件描述符发生变化
                失败: -1

 * 
*/
#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<sys/types.h>
#include<poll.h>
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

    // 初始化检测的文件描述符数组
    struct pollfd fds[1024];
    for(int i = 0; i < 1024; ++i)
    {
        fds[i].fd = -1;
        fds[i].events = POLLIN;
    }
    fds[0].fd = lfd;
    int nfds = 0;
    while(1)
    {
        // 调用poll函数, 让内核检测哪些文件描述符有更新
        int ret = poll(fds, nfds + 1, -1);
        if(ret == -1)
        {
            perror("poll");
            exit(-1);
        }
        else if(ret == 0)
        {
            continue;
        }
        else if(ret > 0)
        {
            // 检测到了有文件描述符发生改变
            if(fds[0].revents & POLLIN)
            {
                // 表示有新的客户端连接
                struct sockaddr_in client_addr;
                int len = sizeof(client_addr);
                int cfd = accept(lfd, (struct sockaddr*)&client_addr, &len);

                // 将新的文件描述符加入集合当中
                for(int i = 1; i < 1024; ++i)
                {
                    if(fds[i].fd == -1)
                    {
                        fds[i].fd = cfd;
                        fds[i].events = POLLIN;
                        break;
                    }
                }
                // 更新最大的文件描述符索引
                nfds = nfds > cfd ? nfds : cfd;
            }
            for(int i = 1; i <= nfds; ++i)
            {
                if(fds[i].events & POLLIN)
                {
                    // 说明这个文件描述符对应的客户端发来数据
                    char buf[1024] = {0};
                    int len = read(fds[i].fd, buf, sizeof(buf));
                    if(len == -1)
                    {
                        perror("read");
                        exit(-1);
                    }
                    else if(len == 0)
                    {
                        printf("client closed\n");
                        close(fds[i].fd);
                        fds[i].fd = -1;
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