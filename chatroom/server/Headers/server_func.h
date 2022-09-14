#ifndef __SERVER_FUNC_H__
#define __SERVER_FUNC_H__

#include "internet.h"
#include "tpool.h"
#include "mysqlite.h"
#include "online.h"
#include "tcp_server.h"
#include "myfile.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>


//?


//任务函数
void *task_routine(void *arg);
//打开数据库并初始化id_counter
void id_init(void);
//将id_counter保存到logout,关闭数据库
void id_destroy(void);

#endif