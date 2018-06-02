//
// Created by 张鹏霄 on 2018/6/2.
//

#include <stdlib.h>
#include "px_timer.h"
#include "sys/time.h"
#include "px_priority_queue.h"

priority_queue timerPq; //存储时间的优先级队列
size_t msNow  = 0; //当前时间

//比较函数，指定大/小堆
int time_comp(void* left, void* right){
    timeNode* l = (timeNode*)left;
    timeNode* r = (timeNode*)right;
    return (l->cutOffTime < r->cutOffTime) ? 1 : 0;
}

void px_time_update()
{

    struct timeval tv;
    gettimeofday(&tv, NULL);
    msNow = (size_t) (tv.tv_sec * 1000 + tv.tv_usec / 1000); // 秒与微秒转为毫秒
}

int px_time_init()
{
    //初始化保存时间节点的优先级队列
    px_pq_init(&timerPq, time_comp, PQ_DEFAULT_SIZE);

    // 更新当前时间
    px_time_update();
    return 0;
}

int px_timeOverNow() //计算等待的时间（最早时间减去原msNow)
{
    int time = -1;

    while(!px_pq_is_empty(&timerPq)){
        px_time_update();

        // 找到最紧急的时间节点
        timeNode* timer_node = (timeNode*) px_pq_top(&timerPq);

        if(timer_node->readyToDeleted){
            px_pq_del(&timerPq);
            free(timer_node);
            continue;
        }

        // 时间差
        time = (int)(timer_node->cutOffTime - msNow);
        break;
    }
    return time;
}

void px_out_of_time()
{
    while(!px_pq_is_empty(&timerPq))
    {
        px_time_update();
        timeNode* timer_node = (timeNode*)px_pq_top(&timerPq);

        if(timer_node->readyToDeleted){
            px_pq_del(&timerPq);
            free(timer_node);
            continue;
        }

        //如果没有超时则退出
        if(timer_node->cutOffTime > msNow){
            return;
        }

        //紧急事件，超时但不应删除
            timer_node->handler(timer_node->request);

        px_pq_del(&timerPq);
        free(timer_node);
    }
}

void px_time_add(httpRequest *request, int timeOut, out_time_handler handler)
{
    px_time_update();
    timeNode* timer_node = (timeNode*)malloc(sizeof(timeNode));
    
    request->time_node = timer_node;
    
    timer_node->cutOffTime = msNow + timeOut;
    timer_node->readyToDeleted = 0;
    timer_node->handler = handler;

    timer_node->request = request;

    px_pq_insert(&timerPq, timer_node);
}