/*
        #include <sys/types.h>
        #include <dirent.h>
        DIR *opendir(const char *name);
        参数:
            name:
                需要打开的目录名称
        return:
            DIR* 类型， 理解为目录流
            失败:
                返回null

        #include <dirent.h>
        struct dirent *readdir(DIR *dirp);
        参数:
            dirp是opendir返回的结果
        return:
            struct dirent, 代表读取的文件信息
            读取到了末尾或失败,返回null

        #include <sys/types.h>
        #include <dirent.h>
        int closedir(DIR *dirp);


*/

#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int getFileNum(const char* path);
int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("%s path\n", argv[0]);
        return -1;
    }

    int num = getFileNum(argv[1]);
    printf("普通文件个数%d\n", num);

    return 0;
}

int getFileNum(const char* path)
{
DIR* dir = opendir(path);
if(dir == NULL)
{
    perror("opendir");
    exit(0);
}
    struct dirent* ptr;
    int total = 0;
    while((ptr = readdir(dir))!= NULL)
    {
        // 获取名称
        char* dname = ptr->d_name;

        // 忽略. 和 ..
        if(strcmp(dname, ".") == 0 || strcmp(dname, "..") == 0)
        {
            continue;
        }
        // 判断是否是普通文件
        if(ptr->d_type == DT_DIR)
        {
            char newpath[256];
            sprintf(newpath, "%s/%s", path, dname);
            total += getFileNum(newpath);
        }
        if(ptr->d_type == DT_REG)
        {
            ++total;
        }
    }
    closedir(dir);
    return total;
}