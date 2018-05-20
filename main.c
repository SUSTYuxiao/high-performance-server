#include <stdio.h>
#include <stdlib.h>


#include "px_tool.h"
#include "px_thread_pool.h"
#include "px_epoll.h"

int main(int argc, char* argv[])
{
    //获取工作路径、端口号、最大线程数
    if(argc != 4)
        printf("错误的参数！\n输入示例：a.out ./ 8888 4\n");
    else
        printf("%s\n%s\n%s\n", argv[1], argv[2], argv[3]);

    //初始化套接字并绑定
    int listen_fd = init_socket(atoi(argv[2]));

    //设置套接字为非阻塞
    //make_socket_not_block

    //创建epoll

    //初始化定时器

    //初始化线程池

    //开始处理请求

    return 0;
}