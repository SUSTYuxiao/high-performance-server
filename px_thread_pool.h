//
// Created by 张鹏霄 on 2018/5/19.
// 线程池
//

#ifndef HIGH_PERFORMANCE_SERVER_THREAD_POOL_H
#define HIGH_PERFORMANCE_SERVER_THREAD_POOL_H

#include <ntsid.h>

typedef struct taskList{    //任务链
    void (*func)(void*);    //回调函数
    void* arg;              //回调函数的参数
    struct taskList *next;
}taskList;

typedef struct threadpool{
    pthread_mutex_t lock;    // 互斥锁
    pthread_cond_t cond;     // 条件变量
    pthread_t *threads;      // 线程
    taskList *head;          // 任务链表
    int thread_count;        // 线程数
    int queue_size;          // 任务链表长
    int shutdown;            // 关机模式
    int started;
}threadpool;

threadpool *threadpool_init(int threadNum);
int threadpool_add(threadpool *pool, void (*func)(void *), void* arg);
int threadpool_destroy(threadpool *pool, int gracegul);

#endif //HIGH_PERFORMANCE_SERVER_THREAD_POOL_H
