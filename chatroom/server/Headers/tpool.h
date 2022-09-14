#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_ 
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
//#include <signal.h>

/* 线程池的任务结点结构体*/
typedef struct thread_pool_task
{
    void *(*routine)(void *);       //任务函数
    void *arg;                      //任务函数的传入参数
    
    struct thread_pool_task *next;  //?
}tpool_task_t;

/*线程池结构体*/
typedef struct thread_pool
{
    int shutdown;               //线程池是否销毁

    int max_thr_num;            //最大线程数
    pthread_t *thr_id;          //线程ID数组首地址

    tpool_task_t *queue_head;   // 任务队列头指针
    tpool_task_t *queue_tail;   // 任务队列尾指针

    pthread_mutex_t queue_lock; 
    pthread_cond_t queue_ready; 
}tpool_t;

/* 创建线程池*/
int tpool_create(int max_thr_num);

/* 向线程池中添加任务*/
int tpool_add_task(void *(routine)(void *), void *arg);

/* 销毁线程池*/
void tpool_destroy();

#endif