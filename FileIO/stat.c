/*
#include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>

       int stat(const char *pathname, struct stat *statbuf);
       作用:
            获取文件的信息
        参数:
            pathname: 操作的文件路径
            statbuf: 结构体变量，传出参数，用于保存文件信息 
        return:
            成功: 0
            失败: -1 设置errno
       int fstat(int fd, struct stat *statbuf);
       int lstat(const char *pathname, struct stat *statbuf);
*/
#include<stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<string.h>
int main(int argc, char* argv[])
{
    // 判断输入的参数是否正确
    if(argc < 2)
    {
        printf("%s filename\n", argv[0]);
        return -1;
    }
    struct stat st;
    int ret = stat(argv[1], &st);
    if(ret == -1)
    {
        perror("stat");
        return -1;
    }

    //用于保存文件类型和权限
    char perms[11] = {0};

    switch (st.st_mode & S_IFMT)
    {
    case  S_IFLNK:
    perms[0] = 'l';
    break;
    case  S_IFDIR:
    perms[0] = 'd';
    break;
    case  S_IFREG:
    perms[0] = '-';
    break;
    case  S_IFBLK:
    perms[0] = 'b';
    break;
    case  S_IFCHR:
    perms[0] = 'c';
    break;
    case  S_IFSOCK:
    perms[0] = 's';
    break;
    case  S_IFIFO:
    perms[0] = 'p';
    break;
    default:
    perms[0] = '?';
    break;
    }

    //判断文件访问权限

    //文件所有者
    perms[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
    perms[1] = (st.st_mode & S_IWUSR) ? 'w' : '-';
    perms[1] = (st.st_mode & S_IXUSR) ? 'x' : '-';

    //文件所在组
    perms[2] = (st.st_mode & S_IRGRP) ? 'r' : '-';
    perms[2] = (st.st_mode & S_IWGRP) ? 'w' : '-';
    perms[2] = (st.st_mode & S_IXGRP) ? 'x' : '-';

    //其他人
    perms[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
    perms[7] = (st.st_mode & S_IWOTH) ? 'w' : '-';
    perms[7] = (st.st_mode & S_IXOTH) ? 'x' : '-';

    // 硬连接数
    int linkNum = st.st_nlink;

    // 文件所有者
    char* fileuesr = getpwuid(st.st_uid)->pw_name;
    // 文件所在组
    char* fileGrp = getgrgid(st.st_gid)->gr_name;
    // 文件大小
    long int fileSize = st.st_size;
    // 文件最后修改时间
    char* time = ctime(&st.st_mtime);
    char mtime[512] = {0};
    strncpy(mtime, time, strlen(time) -1);


    char buf[1024];
    sprintf(buf, "%s %d %s %s %ld %s %s", perms, linkNum, fileuesr, fileGrp, fileSize, mtime, argv[1]);
    printf("%s\n", buf);

    return 0;
}