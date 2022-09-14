#ifndef __MYEPOLL_H__
#define __MYEPOLL_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>

/**
 * @brief 
 *        创建epoll
 * @param max_size //epoll集合内监听的最大数
 * @retval None
 */
void myepoll_create(int max_size);


/**
 * @brief 
 *        将套接子文件描述符添加到epoll集合中
 * @param fd //要添加的套接字文件描述符
 * @retval None
 */
void myepoll_add_in(int fd);


/**
 * @brief 
 *        阻塞等待事件
 * @param events //epoll集合地址
 * @param max_size   //epoll集合内监听的最大数
 * @retval         //发生事件的fd数目
 */
int myepoll_wait_block(struct epoll_event *events,int max_size);


/**
 * @brief 
 *          将套接子文件描述符从epoll集合中删除
 * @param fd  //要删除的套接字文件描述符
 * @retval None
 */
void myepoll_delete_in(int fd);


/**
 * @brief 
 *      销毁epoll
 * @retval None
 */
void myepoll_destroy();

#endif