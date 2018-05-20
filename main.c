#include <stdio.h>
#include <stdlib.h>

#include "px_tool.h"
#include "px_thread_pool.h"
#include "px_epoll.h"

int main(int argc, char* argv[])
{
    //获取工作路径、端口号,最大线程数取决于CPU当前可用核心数目
    if(argc == 3)
        printf("服务器初始化：\nPATH = %s | Port = %s | Max thread num(CPU source) = %d\n\n", argv[1], argv[2], get_CPU_core_num());
    else
        printf("错误的参数！ 示例：[程序名] [工作路径] [端口号] ，如：a.out ./ 8888\n");

    //初始化线程池
    threadpool *threadPoolID = threadpool_init((int)get_CPU_core_num());

    //初始化套接字并绑定
//    int listen_fd = init_socket(atoi(argv[2]));

    //设置套接字为非阻塞
    //make_socket_not_block

    //创建epoll

    //初始化定时器



    //开始处理请求

    return 0;
}