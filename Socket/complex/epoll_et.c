#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<string.h>
#include<fcntl.h>

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

    // 调用epoll_create 创建一个实例
    int epfd = epoll_create(1);

    // 将监听的文件描述符相关的检测信息添加到实例当中
    struct epoll_event epev;
    epev.events  = EPOLLIN;
    epev.data.fd = lfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &epev);

    struct epoll_event epevs[1024];

    while(1)
    {
       int ret = epoll_wait(epfd, epevs, 1024, -1);
       
       if(ret == -1)
       {
        perror("epoll");
        exit(-1);
       }
       printf("ret = %d\n", ret);
       
       for(int i = 0; i < ret; ++i)
       {
            int cur_fd = epevs[i].data.fd;
            if(cur_fd == lfd)
            { // 监听的文件描述符有数据, 有客户端连接
                struct sockaddr_in client_addr;
                int len = sizeof(client_addr);
                int cfd = accept(lfd, (struct sockaddr*)&client_addr, &len);

                // 设置cfd属性非阻塞
                int flag = fcntl(cfd, F_GETFL);
                flag | O_NONBLOCK;
                fcntl(cfd, F_SETFL, flag);

                epev.events = EPOLLIN | EPOLLET;
                epev.data.fd = cfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &epev);
            }
            else
            { 
                // 循环读出所有数据
                int len = 0;
                char buf[5];
                while((len = read(cur_fd, buf, sizeof(buf))) > 0)
                {
                    // 打印数据
                    printf("info recv data: %s\n", buf);
                    write(cur_fd, buf, len);
                }
                if(len == 0)
                {
                    printf("client closed\n");
                }
                else if(len == -1)
                {
                    perror("read");
                    exit(-1);
                }
            }
       }
    }
    close(epfd);
    close(lfd);
    return 0;
}