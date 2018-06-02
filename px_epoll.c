//
// Created by 张鹏霄 on 2018/5/20.
//

#include "px_epoll.h"

struct  epoll_event *event;


int px_epoll_init(int flag)
{
    return epoll_create(flag);
}

int px_epoll_add(int epollFd, int listenFd, httpRequest *request, int events)
{
    EPOLL_SET;
    return epoll_ctl(epollFd, EPOLL_FD_ADD, listenFd, &event);
}

int px_epoll_mod(int epollFd, int listenFd, httpRequest *request, int events)
{
    EPOLL_SET;
    return epoll_ctl(epollFd, EPOLL_FD_MOD, listenFd, &event);
}

int px_epoll_del(int epollFd, int listenFd, httpRequest *request, int events)
{
    EPOLL_SET;
    return epoll_ctl(epollFd, EPOLL_FD_DEL, listenFd, &event);
}

