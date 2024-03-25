/**
 *      #include <sys/types.h>          
        #include <sys/socket.h>

        int socket(int domain, int type, int protocol);
            功能：
                创建一个套接字
            参数：
                domain: 协议族
                    AF_INET: IPv4
                    AF_INET6: IPv6
                type: 通信过程中使用的协议类型
                    SOCK_STREAM: 流式协议
                    SOCK_DGRAM: 报式协议
                protocol: 具体的协议, 一般传递 0表示只有一个协议存在
                    SOCK_STREAM: 流式协议默认使用TCP
                    SOCK_DGRAM: 报式协议默认使用UDP
            return:
                成功: 返回文件描述符fd, 操作的是内核缓冲区
                失败: -1

        int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);
            功能：
                绑定, 将 fd和本地的 IP和端口进行绑定
            参数:
                sockfd:
                    通过socket函数得到的文件描述符
                addr:
                    需要绑定的socket地址, 这个地址封装了IP和端口信息
                addrlen:
                    指定addr大小
        
        int listen(int sockfd, int backlog);
            功能:
                监听socket上的连接
            参数:
                sockfd:
                    通过socket得到的文件描述符
                backlog:
                    未连接和已连接的和的最大值

        int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
            功能:
                接受客户端的连接, 默认阻塞等待
            参数：
                sockfd:
                    用于监听的文件描述符
                addr:
                    传出参数, 记录了连接成功后客户端的地址信息, 包括IP和端口
                addrlen:
                    指定addr的大小
            return:
                成功: 返回用于通信的文件描述符
                失败： -1

        int connect(int sockfd, const struct sockaddr *addr,
                   socklen_t addrlen);
            功能:
                客户端连接服务器
            参数：
                socket:
                    用于通信的文件描述符
                addr:
                    客户端连接的服务器的地址信息
                addrlen:
                    指定addr的大小
            return:
                成功: 0
                失败: -1

 * 
*/