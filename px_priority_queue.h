//
// Created by 张鹏霄 on 2018/6/2.
//

#ifndef HIGH_PERFORMANCE_SERVER_PX_PRIORITY_QUEUE_H
#define HIGH_PERFORMANCE_SERVER_PX_PRIORITY_QUEUE_H

#include <stdio.h>

typedef int (*px_pq_comp)(void *left, void *right);

typedef struct priority_queue{
    void **pqPtr;    // 节点指针
    int size;    // 元素个数
    int capacity;    // 容量
    px_pq_comp comp;    // 大/小堆
}priority_queue;

int px_pq_is_empty(priority_queue *pq);
void* px_pq_top(priority_queue *pq);
int px_pq_del(priority_queue *pq);


#endif //HIGH_PERFORMANCE_SERVER_PX_PRIORITY_QUEUE_H
