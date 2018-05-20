//
// Created by 张鹏霄 on 2018/5/19.
//

#include <printf.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>
#include <stdlib.h>

#include "px_tool.h"

int get_CPU_core_num()
{
    return (int)sysconf(_SC_NPROCESSORS_ONLN);
}

void printError_exit(char *c)
{
    perror(c);
    exit(-1);
}

int init_socket(int portNum)
{
    //判断端口号合法性
    if( portNum < 1025 || portNum > 65535)
    {
        printf("错误的端口号，已使用缺省参数8888\n");
        portNum = 8888;
    }

    //创建socket并返回描述符
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd == -1)
        printError_exit("socket");

    // 使用SO_REUSEADDR使得端口在TIME_WAIT时就可以被重用（上一次连接还未完全结束）
    int sockOptval = 1;
    if(setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (const void*)&sockOptval, sizeof(int)) == -1)
    {
        perror("set socket opt");
        return -1;
    }

    //绑定IP、端口与socket
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons((unsigned short) portNum);
    if(bind(listen_fd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("bind");
        return -1;
    }

    //开始监听
    if (listen(listen_fd, MAX_QUEUE) == -1)
    {
        perror("listen");
        return -1;
    }

    return listen_fd;
}