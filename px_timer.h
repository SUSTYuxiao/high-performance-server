//
// Created by 张鹏霄 on 2018/6/2.
//

#ifndef HIGH_PERFORMANCE_SERVER_PX_TIMER_H
#define HIGH_PERFORMANCE_SERVER_PX_TIMER_H

#include "px_request.h"

#define PQ_DEFAULT_SIZE 10;

typedef int (*out_time_handler)(httpRequest* request);

typedef struct timeNode{
    size_t cutOffTime;                      // 超时时间
    int readyToDeleted;              // 待删除标志
    out_time_handler handler;        // 超时处理函数
    httpRequest* request;      // request请求
}timeNode;

int px_time_init();
int px_timeOverNow();
void px_out_of_time();
void px_time_add(httpRequest *request, int timeOut, out_time_handler handler);
void px_time_del(httpRequest *request);


#endif //HIGH_PERFORMANCE_SERVER_PX_TIMER_H
