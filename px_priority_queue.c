//
// Created by 张鹏霄 on 2018/6/2.
//

#include "px_priority_queue.h"
#include <limits.h>
#include <stdlib.h>
#include <memory.h>

inline void pq_swap(void **left, void **right)
{
    void *tmp = *left;
    *left = *right;
    *right = tmp;
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

void pq_down(priority_queue *pq)//堆的向下调整
{
    int parent = 0;
    int chirld = (parent << 1) +1;

    while(chirld < pq->size)
    {
        if(chirld+1 < pq->size &&
                pq->comp(pq->pqPtr[chirld+1], pq->pqPtr[chirld]))
            chirld++;

        if( pq->comp( &pq->pqPtr[chirld], &pq->pqPtr[parent]) )
        {
            pq_swap(pq->pqPtr[chirld], pq->pqPtr[parent]);
            parent = chirld;
            chirld = (parent << 1) +1;
        }
        else
            break;
    }
}

int px_pq_init(priority_queue *node, px_pq_comp comp, int capacity)
{
    node->pqPtr = (void **) malloc(sizeof(void *) * capacity);
    if(!node->pqPtr)
        perror("malloc for priority_queue failed");

    node->size = 0;
    node->capacity = capacity;
    node->comp = comp;
    return 0;
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
    pq_swap(&pq->pqPtr[0], &pq->pqPtr[pq->size - 1]);
    pq->size--;
    pq_down(pq);
}

int px_pq_resize(priority_queue *pq, int newCapacity)
{
    void **newPtr = (void **)malloc(sizeof(void *) * newCapacity);
    if(!newPtr)
    {
        perror("malloc failed for pqPtr");
        return -1;
    }

    memcpy(newPtr, pq->pqPtr, sizeof(void*) * pq->size);
    free(pq->pqPtr);
    pq->pqPtr = newPtr;
    pq->capacity = newCapacity;
}

int px_pq_insert(priority_queue *pq, void* item)
{
    if(pq->size+1 == pq->capacity)
        px_pq_resize(pq, get_capacity_size(pq));

    pq->pqPtr[++pq->size] = item;

    return 0;
}