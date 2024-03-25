/**
 *      #include <sys/epoll.h>

        int epoll_create(int size);
            创建一个新的epoll实例。在内核中创建了一个数据, 这个数据中有两个比较重要的数据, 一个需要检测的文件描述符的信息
            还有一个是就绪列表, 存放检测到数据发生改变的文件描述符的信息(双向链表)
            参数:
                忽略值, 任意输入一个大于 0的数
            return:
                成功: 文件描述符, 操作epoll实例
                失败: -1
        int epoll_create1(int flags);

        int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
            对epoll实例进行管理: 添加文件描述符信息, 删除信息, 修改信息
            参数:
                epfd:
                    epoll实例对应的文件描述符
                op:
                    要进行什么操作
                    EPOLL_CTL_ADD: 添加
                    EPOLL_CTL_MOD: 修改
                    EPOLL_CTL_DEL: 删除
                fd:
                    要检测的文件描述符
                event:
                    检测文件描述符具体的事情, 使用下面的结构体
                    struct epoll_event {
                        uint32_t     events;      
                        epoll_data_t data;        
                    };
                    events 常用的epoll检测事件:
                        EPOLLIN
                        EPOLLOUT
                        EPOLLERR
                    data: 
                         typedef union epoll_data {
                                void        *ptr;
                                int          fd;
                                uint32_t     u32;
                                uint64_t     u64;
                            } epoll_data_t;

        int epoll_wait(int epfd, struct epoll_event *events,
                      int maxevents, int timeout);
            epfd:
                epoll实例对应的文件描述符
            events:
                传出参数， 保存了发生了变化的文件描述符的信息
            maxevents:
                第二个参数结构体数组的大小
            timeout:
                阻塞时间
                0: 不阻塞
                -1: 阻塞, 直到检测到fd数据发生变化
                >0: 阻塞时长
            return:
                成功: 返回发生变化的文件描述符的个数, >0
                失败: -1
 * 
*/
#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<string.h>

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
                epev.events = EPOLLIN;
                epev.data.fd = cfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &epev);
            }
            else
            { // 有数据到达
                char buf[1024] = {0};
                int len = read(cur_fd, buf, sizeof(buf));
                if(len == -1)
                {
                    perror("read");
                    exit(-1);
                }
                else if(len == 0)
                {
                    printf("client closed\n");
                    epoll_ctl(epfd, EPOLL_CTL_DEL, cur_fd, NULL);
                    close(cur_fd);
                }
                else if(len > 0)
                {
                    printf("read data: %s\n", buf);
                    write(cur_fd, buf, strlen(buf) + 1);
                }

            }
       }
    }
    close(epfd);
    close(lfd);
    return 0;
}