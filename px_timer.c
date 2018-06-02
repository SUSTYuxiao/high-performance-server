//
// Created by 张鹏霄 on 2018/6/2.
//

#include <stdlib.h>
#include "px_timer.h"
#include "sys/time.h"
#include "px_priority_queue.h"

priority_queue timer; //存储时间的优先级队列
size_t msNow  = 0; //当前时间

//比较函数，指定大/小堆
int time_comp(void* left, void* right){
    timeNode* l = (timeNode*)left;
    timeNode* r = (timeNode*)right;
    return (l->key < r->key) ? 1 : 0;
}

void px_time_update()
{

    struct timeval tv;
    gettimeofday(&tv, NULL);
    msNow = (size_t) (tv.tv_sec * 1000 + tv.tv_usec / 1000); // 秒与微秒转为毫秒
}

int px_pq_init(priority_queue *node, px_pq_comp comp, size_t capacity)
{
    node->pqPtr = (void **) malloc(sizeof(void *) * capacity + 1); //多一个头节点
    if(!node->pqPtr)
        perror("malloc for priority_queue failed");

    node->size = 0;
    node->capacity = capacity + 1;
    node->comp = comp;
    return 0;
}

int px_time_init()
{
    //初始化保存时间节点的优先级队列
    int rc = px_pq_init(&timer, time_comp, PQ_DEFAULT_SIZE);

    // 更新当前时间
    px_time_update();
    return 0;
}

int px_find_time()
{
    int time;
    // 返回队列中最早时间和当前时间之差
    while(!px_pq_is_empty(&timer)){
        px_time_update();

        // timer_node指向最小的时间
        timeNode* timer_node = (timeNode*) px_pq_top(&timer);

        // 如果已删则释放此节点（tk_del_timer只置位不删除）
        if(timer_node->readyToDeleted){
            int rc = px_pq_del(&timer);
            free(timer_node);
            continue;
        }

        // 此时timer_node为时间最小节点，time为优先队列里最小时间减去当前时间
        time = (int)(timer_node->key - msNow);
        break;
    }
    return time;
}