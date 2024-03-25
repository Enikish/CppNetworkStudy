/*
 *     #include <sys/types.h>
       #include <sys/stat.h>
       int mkfifo(const char *pathname, mode_t mode);
       参数：
        pathname:
            管道名称的路径
        mode:
            文件的权限, 和open的 mode是一样的
    return:
        成功:返回 0
        失败:返回-1
    有名管道的注意事项:
        1. 一个为只读而打开一个管道的进程会阻塞, 直到另外一个进程为只写打开管道
        2. 一个为只写而打开一个管道的进程会阻塞, 直到另外一个进程为只读打开管道
    读管道；
        管道中有数据, read返回实际读到的字节数
        管道中无数据:
            管道写端被全部关闭, read返回0
            写端没有全部被关闭. read阻塞等待
    写管道:
        管道读端被全部关闭, 进行异常终止
        管道读端没有全部关闭:
            管道已经满了, write会阻塞
            管道没有满, write将数据写入, 并返回实际写入的字节数
 * 
*/
#include <sys/types.h>
#include <sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    int ret =  access("fifo1", F_OK);
    if(ret == -1)
    {
        printf("fifo not exist creat one\n");
        ret = mkfifo("fifo1", 0664);
        if(ret == -1)
        {
            perror("mkfifo");
            exit(0);
        }
    }
    
    return 0;
}