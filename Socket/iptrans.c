/**
 * #include <arpa/inet.h>

    // p: 点分十进制字符串
    int inet_pton(int af, const char *src, void *dst);
        af:
            地址族:
                AF_INET/ AF_INET6
        src:
            需要转换的点分十进制的IP字符串
        dst:
            转换后的结果保存在这个里面

    const char *inet_ntop(int af, const void *src,
                             char *dst, socklen_t size);
        // 将IPv4或者IPv6的地址转换成点分十进制的字符串, 参数和上同
        socklen_t size:
            指定dst数组的大小
        
        return:
            返回转换后的数据的地址
 * 
*/
#include<stdio.h>
#include<arpa/inet.h>

int main()
{
    //创建一个ip字符串
    char buf[] = "192.168.2.1";

    // 将点分十进制的IP字符串转换成网络字节序的整数
    unsigned int num = 0;
    inet_pton(AF_INET, buf, &num);
    unsigned char* p  = (unsigned char*)&num;

    printf("%d.%d.%d.%d\n", *p, *(p + 1), *(p + 2), *(p + 3));

    // 将网络字节序的IP整数转换成点分十进制的IP字符串
    char ip[16] = "";
    const char* str = inet_ntop(AF_INET, &num, ip, 16);
    printf("%s\n", str);
    return 0;
}