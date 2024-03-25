#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>


int main()
{
    /*
    //s_size read(int fd, void* buf, size_t count)
    // fd: 文件描述符
    // buf: 数据存放的地方
    // count: 指定数组的大小
    // return: 
        成功:
        >0: 返回实际读取到底字节数
        =0: 文件已读取完
        失败:
        返回-1,并设置errno
    */

    int srcfd = open("create.txt", O_RDONLY);
    if(srcfd == -1)
    {
        perror("open");
        return -1;
    }
    int dstfd = open("cpy.txt", O_WRONLY | O_CREAT, 0666);
    
    char buf[1024] = {0};
    
    int len = 0;
    
    while((len = read(srcfd, buf, sizeof(buf))) > 0)
    {
        write(dstfd, buf, len);
    }

    close(srcfd);
    close(dstfd);
    return 0;
}