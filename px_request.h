//
// Created by 张鹏霄 on 2018/6/2.
//

#ifndef HIGH_PERFORMANCE_SERVER_PX_REQUEST_H
#define HIGH_PERFORMANCE_SERVER_PX_REQUEST_H

typedef struct httpRequest
{
    char* root; //工作路径
    int listenFd;
    int epollFd;
    int pos;
    int last;
    int state;
}httpRequest;

void px_http_init(httpRequest *request, int epollFd, int listenFd, char *path);

#endif //HIGH_PERFORMANCE_SERVER_PX_REQUEST_H
