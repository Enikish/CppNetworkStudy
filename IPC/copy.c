/**
 * 使用内存映射实现文件拷贝的功能
 * 
 * 思路：
 *      1. 对原始文件进行内存映射
 *      2. 创建一个新文件(拓展该文件)
 *      3. 把新文件的数据映射到内存中
 *      4. 通过内存拷贝将第一个文件的内存数据拷贝到新的文件内存中
 *      5. 释放资源
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
int main()
{

    int fd = open("hel.txt", O_RDWR);
    if(fd == -1)
    {
        perror("open");
        exit(0);
    }

    int fd1 = open("cpy.txt", O_RDWR | O_CREAT, 0664);
    if(fd1 == -1)
    {
        perror("open");
        exit(0);
    }

   int len = lseek(fd, 0, SEEK_END);

    truncate("cpy.txt", len);
    write(fd1, " ", 1);

    void* ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    void* ptr1 = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);

    memcpy(ptr1, ptr, len);

    munmap(ptr1, len);
    munmap(ptr, len);
    close(fd1);
    close(fd);
    return 0;
}