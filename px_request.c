//
// Created by 张鹏霄 on 2018/6/2.
//

#include "px_request.h"

void px_http_init(httpRequest *request, int epollFd, int listenFd, char *path)
{
    request->listenFd = listenFd;
    request->epollFd = epollFd;
    request->root = path;

    request->pos = 0;
    request->last = 0;
    request->state = 0;
    //INIT_LIST_HEAD(&(request->list));
}