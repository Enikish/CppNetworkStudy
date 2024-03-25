/*
    #include <unistd.h>
    int chdir(const char *path);
        作用:
            修改进程的工作目录

    #include <unistd.h>
    char *getcwd(char *buf, size_t size);
        作用:
            获取当前工作目录
        参数:
            buf:
                存储的路径，指向一个数组
            size:
                数组的大小
        return:
            返回指向的一块内存，数据就是第一个参数
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
int main()
{

    char buf[128] = {0};
    getcwd(buf, sizeof(buf));
    printf("%s\n",buf);

    int ret = chdir("../");
    if(ret == -1)
    {
        perror("chdir");
        return -1;
    }

    int fd = open("chdir.txt", O_CREAT|O_RDWR, 0664);
    if(fd == -1)
    {
        perror("open");
        return -1;
    }
    close(fd);

    char cur_buf[128] = {0};
    getcwd(cur_buf, sizeof(cur_buf));
    printf("%s\n",cur_buf);

    return 0;
}