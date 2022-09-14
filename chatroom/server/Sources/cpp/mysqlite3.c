#include "mysqlite.h"

#define DB_PATH "record/database/chatroom.db"

static sqlite3 *db;         //所有注册的用户表的句柄

//创建数据库
int mysqlite3_open()
{
    int ret; 
    //打开或者创建数据库
    sqlite3 *ppdb;
    ret = sqlite3_open(DB_PATH,&ppdb);
    if(ret != SQLITE_OK)
    {
        printf("sqlite3 open: %s\n",sqlite3_errmsg(ppdb));
        return SQL_FAILURE;
    }
    else
    {
        printf("SQLITE3  SUCCESS!\n");
        return SQL_SUCCESS;
    }
} 


//数据库簇函数 -- 插入、删除、修改数据
//执行SQL语句
int mysqlite3_exec(const char *sql)
{
    printf("sql = %s\n", sql);
    if(SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, NULL))
    {
        printf("mysqlite_exec: %s\n", sqlite3_errmsg(db));
        return SQL_FAILURE;
    }
    return SQL_SUCCESS;
}

//获取logout表中的lid的回调函数
static int logout_callback(void *arg , int column, char **f_value, char **f_name)
{
    int *data = (int *)arg;
    *data = atoi(f_value[0]);       //获取logout的lid的值
    return 0;
}

//获取f_value里的查询到的结果
static int online_callback(void *arg , int column, char **f_value, char **f_name)
{
    printf("column = %d\n", column);
    char **tmp = (char **)arg;
    int i;
    for(i = 0; i < column; i++)
    {
        strcpy(tmp[i], f_value[i]);
    }
    return 0;
}

static int find_callback(void *arg, int column, char **f_value, char **f_name)
{
    strcpy((char *)arg, f_value[0]);
    return 0;
}

int mysqlite3_getdata(const char * sql, void *data, int flags)
{
    printf("getdata: sql = %s\n", sql);
    int (*callback)(void *, int, char **, char **);
    switch (flags)
    {
        case LOGOUT:
            callback = logout_callback;
            break;
        case ONLINE:
            callback = online_callback;
            break;
        case FIND:
            callback = find_callback;
            break;
        default:
            printf("mysqlite_getdata: flags invalid argment\n");
            return SQL_FAILURE;
    }
    if(SQLITE_OK != sqlite3_exec(db, sql, callback, data, NULL))
    {
        printf("mysqlite_getdata: %s", sqlite3_errmsg(db));
        return SQL_FAILURE;
    }
    return SQL_SUCCESS;
}

//执行SQL查询
int mysqlite3_get_table(const char *sql, char ***result, int *row, int *col)
{
    int ret = sqlite3_get_table(db, sql, result, row, col, NULL);
    if(SQLITE_OK != ret)
    {
        printf("mysqlite_get_table: %s", sqlite3_errmsg(db));
        return SQL_FAILURE;
    }
    return SQL_SUCCESS;
}



//关闭数据库
int mysqlite3_close()
{
    if(SQLITE_OK != sqlite3_close(db))
    {
        printf("mysqlite_close: %s\n", sqlite3_errmsg(db));
        return SQL_FAILURE;
    }
    else
    {
        printf("数据库关闭成功!\n");
        return SQL_SUCCESS;
    }
}