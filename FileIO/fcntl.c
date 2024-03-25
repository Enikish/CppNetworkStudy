/*
    #include <unistd.h>
    #include <fcntl.h>

    int fcntl(int fd, int cmd, ...);
    参数:
        fd:
            表示需要操作的文件描述符
        cmd:
            表示对文件描述符进行如何操作
            1. F_DUPFD: 复制文件描述符, 复制的是第一个参数fd, 得到一个新的文件描述符
            2. F_GETFL: 获取指定的文件描述符文件状态flag
                获取的flag是通过open函数传递的flag是相同的
            3. F_SETFL: 设置文件描述符文件状态flag
                必选项: O_RDONLY, O_WRONLY, O_RDWR 不可修改
                可选项: O_APPEND, O_NONBLOCK
                    O_APPEND 表示追加数据
                    O_NONBLOCK 设置成非阻塞
                阻塞和非阻塞:
                    描述的是函数调用的行为
*/

#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
int main()
{
    // int fd = open("1.txt", O_RDONLY);
    // int ret = fcntl(fd, F_DUPFD);
    int fd = open("1.txt", O_RDWR);

    // 修改文件描述符标记
    if(fd == -1)
    {
        perror("open");
        return -1;
    }
    // 获取文件描述符状态flag
    int flag = fcntl(fd, F_GETFL);
    flag |= O_APPEND;
    int ret = fcntl(fd, F_SETFL, flag);
    if(ret == -1)
    {
        perror("fcntl");
        return -1;
    }
    char* str = "adios";
    write(fd, str, strlen(str));
    close(fd);

    return 0;
}