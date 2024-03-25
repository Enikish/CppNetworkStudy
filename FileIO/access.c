/*
#include <unistd.h>
int access(const char *pathname, int mode);
    作用：
        判断某个文件是否具有某个权限，或者判断文件是否存在
    参数：
        pathname:
            判断文件路径
        mode:
            R_OK: 判断是否有读权限
            W_OK: 判断是否有写权限
            X_OK: 判断是否有执行权限
            F_OK: 判断文件是否存在
        return:
            成功: 0
            失败: -1

*/
#include<unistd.h>
#include<stdio.h>
int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("access filename\n");
        return -1;
    }
    int f_ok = access(argv[1], F_OK);
    if(f_ok)
    {
        printf("file %s does not exist\n", argv[1]);
        return 0;
    }
    printf("file exists\n");
    return 0;
}