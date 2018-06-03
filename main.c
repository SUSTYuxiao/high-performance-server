#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include "px_tool.h"
#include "px_thread_pool.h"
#include "px_epoll.h"
#include "px_request.h"
#include "px_timer.h"


int main(int argc, char* argv[])
{
    //获取工作路径、端口号,最大线程数取决于CPU当前可用核心数目
    if(argc == 3)
        printf("服务器初始化：\nPATH = %s | Port = %s | Max thread num(CPU source) = %d\n\n", argv[1], argv[2], get_CPU_core_num());
    else
        printf("错误的参数！ 示例：[程序名] [工作路径] [端口号] ，如：a.out ./ 8888\n");

    //初始化线程池
    threadpool* threadPoolID = px_threadpool_init((int) get_CPU_core_num());

    //初始化套接字并绑定
    int listenFd = px_init_socket(atoi(argv[2]));

    //创建epollFd
    int epollFd = px_epoll_init(MAX_EVENTS);

    //初始化httpRequest结构
    httpRequest *request = (httpRequest *) malloc(sizeof(httpRequest));
    px_request_init(request, epollFd, listenFd, argv[1]);

    //注册lstenFd到epoll
    px_epoll_add(epollFd, listenFd, request, (EPOLLIN | EPOLLET));

    //初始化定时器
    px_time_init();

    //工作
    while (1)
    {
        int timeOverNow = px_timeOverNow();

        int eventsNum = epoll_wait(epollFd, event, MAX_EVENTS, -1);

        //删除已超时的
        px_out_of_time();

        //遍历event数组
        work(epollFd, listenFd, event, eventsNum, argv[1], threadPoolID);
    }

    return 0;
}