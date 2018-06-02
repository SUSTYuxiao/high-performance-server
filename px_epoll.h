//
// Created by 张鹏霄 on 2018/5/20.
//

#ifndef HIGH_PERFORMANCE_SERVER_PX_EPOLL_H
#define HIGH_PERFORMANCE_SERVER_PX_EPOLL_H

#include "px_request.h"

#define MAX_EVENTS 1024;
#define EPOLL_SET                       \
    do                                  \
    {                                   \
    struct epoll_event event;           \
    event.data_ptr = (void *) request;  \
    event.events = events;              \
    }while(0);

struct  epoll_event *event;


int px_epoll_init(int flag);
int px_epoll_add(int epollFd, int listenFd, httpRequest *request, int events);
int px_epoll_mod(int epollFd, int listenFd, httpRequest *request, int events);
int px_epoll_del(int epollFd, int listenFd, httpRequest *request, int events);


#endif //HIGH_PERFORMANCE_SERVER_PX_EPOLL_H
