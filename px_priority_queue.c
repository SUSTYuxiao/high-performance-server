//
// Created by 张鹏霄 on 2018/6/2.
//

#include "px_priority_queue.h"
#include <limits.h>

inline void pq_swap(void *left, void *right)
{

}

inline int get_capacity_size(priority_queue *pq)
{
    int newSize = pq->capacity << 1;

    //溢出
    if(pq->capacity > (INT_MAX >> 1))
        newSize = INT_MAX;

    return newSize;
}

void pq_up(priority_queue *pq)//堆的向上调整
{
    int chirld = pq->size-1;
    int parent = (chirld - 1) >> 1;

    while(chirld > 0)
    {
        if( pq->comp( pq->pqPtr[chirld], pq->pqPtr[parent]) )
        {
            pq_swap(pq->pqPtr[chirld], pq->pqPtr[parent]);
            chirld = parent;
            parent = (chirld - 1) >> 1;
        }
        else
            break;
    }
}

int px_pq_is_empty(priority_queue *pq)
{
    return pq->size == 0 ? 1 : 0;
}

void* px_pq_top(priority_queue *pq)
{
    if(pq->size == 0)
        return (void *) -1;

    return pq->pqPtr[0];
}

int px_pq_del(priority_queue *pq)
{

}

int px_pq_resize(priority_queue *pq, int newSize)
{

}

int px_pq_insert(priority_queue *pq, void* item)
{
    if(pq->size+1 == pq->capacity)
        px_pq_resize(pq, get_capacity_size(pq));

    pq->pqPtr[++pq->size] = item;

    return 0;
}