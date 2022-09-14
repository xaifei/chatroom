#ifndef __MYSQLITE3_H__
#define __MYSQLITE3_H__
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sqlite3.h>

#define SQL_SUCCESS 0
#define SQL_FAILURE -1

enum getdata_flags      //mysqlite_getdata flags
{
    LOGOUT,     //
    ONLINE,    //在线
    FIND,      //查找
};

//打开数据表
int mysqlite3_open();


//数据库簇函数 -- 插入、删除、修改数据
int mysqlite3_exec(const char *sql);//?

int mysqlite3_getdata(const char * sql, void *data, int flags);//?

//执行SQL查询
int mysqlite3_get_table(const char *sql, char ***result, int *row, int *col);//?

//关闭数据库
int mysqlite3_close();

#endif 