#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 

#define TCP_SUCCESS 1
#define TCP_FAILURE -1
#define EXIT_ERROR -1

#define LISTEN_NUM 10      //listen函数同时处理请求的最大数

//创建套接字，绑定，监听
int server_create(const char *Ip,int Port);
//等待链接
int server_accept(int sfd);
//发送
int send_msg(int cfd,const void *buf,int buf_len);

#endif