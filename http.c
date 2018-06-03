//
// Created by 张鹏霄 on 2018/6/3.
//

#include <stdlib.h>
#include <zconf.h>
#include <errno.h>
#include "http.h"
#include "px_request.h"
#include "px_epoll.h"

int px_http_parse_request_line(httpRequest *request)
{
    //TODO
}

void do_request(void* ptr){
    httpRequest* request = (httpRequest*)ptr;
    int fd = request->fd;
    char *path = request->root;

    char filename[256];
    struct stat sbuf;
    int rc;
    char* plast = NULL;

    ssize_t readRet;    //read函数返回值
    int leastSize;      //缓冲区剩余字节

    px_time_del(request);

    while(1)
    {
        //plast指向缓冲区可写入部分的第一个字节
        //plast = &request->buff[request->last % BUF_MAX];

        leastSize = MIN(BUF_MAX - (request->last - request->pos) - 1, BUF_MAX - request->last % BUF_MAX);
        readRet = read(fd, plast, leastSize);

        // 文件尾或无可读数据，断开连接
        if (readRet == 0)
            goto err;

        // EAGAIN则重置定时器，重新注册，在不断开TCP连接情况下重新等待下一次用户请求
        if (readRet < 0)
        {
            if (errno == EAGAIN) //重置定时器,重新注册，不断开tcp
                break;
            else
                goto err;
        }

        // 更新读到的总字节数
        request->last += readRet;

        // 解析报头
        rc = px_http_parse_request_line(request);
        if (rc == EAGAIN)
            continue;
        else if (rc != 0)
            goto err;

        //TODO

    }

    err:
    close:
    // 发生错误或正常关闭
    // 关闭相应连接描述符，释放用户请求数据结构
    px_request_close(request);
}

