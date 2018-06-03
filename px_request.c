//
// Created by 张鹏霄 on 2018/6/2.
//

#include <stdlib.h>
#include <zconf.h>
#include "px_request.h"

void px_request_init(httpRequest *request, int epollFd, int listenFd, char *path)
{
    request->fd = listenFd;
    request->epollFd = epollFd;
    request->root = path;

    request->pos = 0;
    request->last = 0;
    request->state = 0;
    //INIT_LIST_HEAD(&(request->list));
}

int px_request_close(httpRequest *request){
    close(request->fd);
    free(request);
    return 0;
}