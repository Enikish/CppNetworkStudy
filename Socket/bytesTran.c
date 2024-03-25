/**
 *      #include <arpa/inet.h>
        h: host
        n: network
        s: short

        网络通信时, 需要将主机字节序(小端)转成网络字节序(大端)
        另外一段获取到数据以后根据情况将网络字节序转换成主机字节序
        作用：
            转换端口
        uint32_t htonl(uint32_t hostlong);
            
            网络字节序
            
        uint16_t htons(uint16_t hostshort);
         
        作用：
            转换IP
        uint32_t ntohl(uint32_t netlong);
            l: long
            
        uint16_t ntohs(uint16_t netshort);


    #include <arpa/inet.h>

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
    // 转换端口
    unsigned short a = 0x3142;
    unsigned short b = htons(a);
    printf("%x\n", b);

    // 转换IP
    // htonl
    char buf[4] = {192, 168, 1, 100};
    int num = *(int*)buf;
    unsigned long sum = htonl(num);
    unsigned char* p = (char*)&sum;
    printf("%d.%d.%d.%d\n", *p, *(p + 1), *(p + 2), *(p + 3));

    // ntohl
    unsigned char buf1[4] = {192, 1, 168, 2};
    int num1 = *(int*)buf1;
    int sum1 = ntohl(num1);
    unsigned char* p1 = (unsigned char*)&sum1;
    printf("%d.%d.%d.%d\n", *p1, *(p1 + 1), *(p1 + 2), *(p1 + 3));

    int sum2 = htonl(num1);
    unsigned char* p2 = (unsigned char*)&sum2;
    printf("%d.%d.%d.%d\n", *p2, *(p2 + 1), *(p2 + 2), *(p2 + 3));

    return 0;
}