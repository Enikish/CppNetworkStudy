/*
    #include <sys/stat.h>    
    int chmod(const char *pathname, mode_t mode);
    修改文件权限:
    参数：
        pathname: 需要修改的文件路径
        mode: 需要修改的权限值, 使用八进制
    return:
        成功: 0
        失败: -1

    #include <unistd.h>
    #include <sys/types.h>
    int truncate(const char *path, off_t length);
    作用:
        缩减或者拓展文件的尺寸至指定的大小
    参数:
        path:
            需要修改的文件路径
        length:
            需要修改成的最终大小
    return:
        成功: 0
        失败: -1

*/
#include<sys/stat.h>
#include<stdio.h>
#include<unistd.h>
int main()
{

    int ret = truncate("cpy.txt", 20);
    if(ret == -1)
    {
        perror("truncate");
        return -1;
    }
    return 0;
}