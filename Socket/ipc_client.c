#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/un.h>
#include<fcntl.h>
int main()
{
    unlink("client.sock");

    // socket
    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(fd == -1)
    {
        perror("socket");
        exit(-1);
    }

    // bind
    struct sockaddr_un addr;
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path, "client.sock");
    int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == -1)
    {
        perror("bind");
        exit(-1);
    }

    // connect
    struct sockaddr_un server_addr;
    server_addr.sun_family = AF_LOCAL;
    strcpy(server_addr.sun_path, "server.sock");
    ret = connect(fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(ret == -1)
    {
        perror("connect");
        exit(-1);
    }


    // communicate
    int num = 0;
    while(1)
    {
        char buf[128] = {0};
        sprintf(buf, "hello i'm client %d\n", num++);
        send(fd, buf, sizeof(buf) + 1, 0);


        int len = recv(fd, buf, sizeof(buf), 0);
        if(len == -1)
        {
            perror("recv");
            exit(-1);
        }
        else if(len > 0)
        {
            printf("recv data:%s\n", buf);
            send(fd, buf, len, 0);
        }
        else if(len == 0)
        {
            printf("connect closed..\n");
            break;
        }
        sleep(1);
    }
    close(fd);
    return 0;
}