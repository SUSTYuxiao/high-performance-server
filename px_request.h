//
// Created by 张鹏霄 on 2018/6/2.
//

#ifndef HIGH_PERFORMANCE_SERVER_PX_REQUEST_H
#define HIGH_PERFORMANCE_SERVER_PX_REQUEST_H

#include "px_timer.h"

typedef struct httpRequest
{
    char* root;     //工作路径
    int fd;         //对应描述符
    int epollFd;
    timeNode* time_node;

    int pos;
    int last;
    int state;
}httpRequest;

void px_http_init(httpRequest *request, int epollFd, int listenFd, char *path);
int px_http_close(httpRequest *request);

#endif //HIGH_PERFORMANCE_SERVER_PX_REQUEST_H
