//
// Created by 张鹏霄 on 2018/5/19.
//

#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include "px_tool.h"
#include "px_thread_pool.h"

//TODO 平滑关闭线程池

void* worker(void* p)
{
    threadpool *pool = (threadpool*)p;

    while (1)
    {
        pthread_mutex_lock(&pool->cond);

        if(pool->quit == 1)
            break;
        pool->threadLeast++; //准备工作，可用线程数++

        while(pool->head->next == NULL)
            pthread_cond_wait(&pool->cond, &pool->mutex);

        //被唤醒，开始工作
        pool->threadLeast--;
        taskNode *cur = pool->head->next;
        pool->head->next = cur->next;
        pthread_mutex_unlock(&pool->mutex);

        //执行回调函数
        cur->func(cur->arg);
        free(cur);
    }

    pool->threadLeast--;
    pthread_mutex_unlock(&pool->mutex);
    pthread_exit(NULL);
}

threadpool* threadpool_init(int threadNum)
{
    //分配线程池空间
    threadpool *pool;
    if (! (pool = (threadpool *) malloc(sizeof(threadpool))) )
        printError_exit("malloc failed(pool)");

    //线程池初始化
    memset(pool, 0x00, sizeof(threadpool));

    if (pthread_mutex_init( &(pool->mutex), NULL) ) //初始化互斥锁
        printError_exit("mutex init failed(pool)");
    if (pthread_cond_init( &(pool->cond), NULL) ) //初始化条件变量
        printError_exit("cond init failed(pool)");

    //head指向对链表是带头链表
    pool->threadMax = threadNum;
    pool->head->func = NULL;
    pool->head->arg = NULL;
    pool->head->next = NULL;

    //创建线程
    for (int i = 0; i < pool->threadMax; ++i)
        pthread_create(&(pool->threads[i]), NULL, worker, (void *) pool);

    return pool;
}

int threadpool_add(threadpool *pool, void (*func)(void *), void* arg)
{
    if (!pool || !func)
        printError_exit("NULL(pool or func)");

    //申请锁
    if (pthread_mutex_unlock( &(pool->mutex) ))
        goto error;

    //判断是否准备销毁
    if (pool->quit)
        printError_exit("poll is ready to shutdown");

    //初始化任务
    taskNode *node = (taskNode*) malloc(sizeof(node));
    if(!node)
        goto error;
    node->func = func;
    node->arg = arg;
    node->next = NULL;

    //头插taskNode
    node->next = pool->head->next;
    pool->head->next = node;

    pthread_cond_signal(&pool->cond);

    error:
    if(pthread_mutex_lock(&pool->mutex) != 0)
        return -1;

    return 0;
}

int threadpool_destroy(threadpool *pool)
{
    if (pool == NULL)
        return 0;

    if (pool->quit)
        return 0;
    pool->quit =1;


    pthread_mutex_unlock(&pool->mutex);

    pthread_cond_broadcast(&pool->cond);

    pthread_mutex_unlock(&pool->mutex);

    for(int i = 0; i < pool->threadMax; i++)
    {
        if(pthread_join(pool->threads[i], NULL) != 0)
            printError_exit("join error");
    }

    pthread_mutex_destroy(&(pool->mutex));
    pthread_cond_destroy(&(pool->cond));

    free(pool->threads);

    taskNode *cur = NULL;

    while (pool->head->next)
    {
        cur = pool->head->next;
        pool->head->next = cur->next;
        free(cur);
    }
    free(pool);

    return 0;
}