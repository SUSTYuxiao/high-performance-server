//
// Created by 张鹏霄 on 2018/5/19.
// 线程池
//

#ifndef HIGH_PERFORMANCE_SERVER_THREAD_POOL_H
#define HIGH_PERFORMANCE_SERVER_THREAD_POOL_H

#include <ntsid.h>

typedef struct taskNode{    //任务链
    void (*func)(void*);    //回调函数
    void* arg;              //回调函数的参数
    struct taskNode *next;
}taskNode;

typedef struct threadpool{
    pthread_mutex_t mutex;    // 互斥锁
    pthread_cond_t cond;     // 条件变量
    pthread_t *threads;      // 线程
    taskNode *head;          // 任务链表头节点
    int threadLeast;         // 空闲线程
    int threadMax;             // 最大线程数
    int quit;                // 等待销毁
}threadpool;

threadpool* px_threadpool_init(int threadNum);
int px_threadpool_add(threadpool *pool, void (*func)(void *), void *arg);
int px_threadpool_destroy(threadpool *pool);

#endif //HIGH_PERFORMANCE_SERVER_THREAD_POOL_H
