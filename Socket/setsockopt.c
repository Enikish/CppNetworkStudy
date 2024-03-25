/**
 *      #include <sys/types.h>          
        #include <sys/socket.h>

        int getsockopt(int sockfd, int level, int optname,
                        void *optval, socklen_t *optlen);
        int setsockopt(int sockfd, int level, int optname,
                        const void *optval, socklen_t optlen);
            参数:
                sockfd:
                    要操作的文件描述符
                level:
                    级别 SOL_SOCKET(端口复用级别)
                optname:
                    端口复用的值(int)
                    1: 可以复用
                    2: 不可复用
                optlen:
                    optval参数的大小
    端口复用, 设置的时机是在服务器绑定端口之前
 * 
*/