//
// Created by 张鹏霄 on 2018/5/20.
//

#include <zconf.h>
#include "px_epoll.h"
#include "px_tool.h"
#include "px_thread_pool.h"

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

void work(int epollFd, int listenFd, struct epoll_event* events, int eventsNum, char *path, threadpool *threadPoolID)
{
    for(int i = 0; i < eventsNum; i++){
        // 获取有事件产生的描述符
        httpRequest* request = (httpRequest*)(events[i].data.ptr);

        // 有事件发生的描述符为监听描述符
        if(request->fd == listenFd)
            px_accept(listenFd, epollFd, path);
        else
        {
            // 描述符错误、被挂断或非可读
            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN)))
            {
                close(request->fd);
                continue;
            }

            //加入到线程池//TODO
            px_threadpool_add(threadPoolID, do_request, events[i].data.ptr);
            // do_request(events[i].data.ptr);
        }
    }
}