#include"myepoll.h"

int epoll_fd;

//创建epoll对象
void myepoll_create(int max_size)
{
    epoll_fd=epoll_create(max_size);
    if(epoll_fd==-1)
    {
        perror("epoll_create error");
    }
}

//将套接子文件描述符添加到epoll集合中
void myepoll_add_in(int fd)
{
    struct epoll_event ev;
    //设置监听socket可读
    ev.data.fd = fd;
    ev.events  = EPOLLIN;
    //将所有要监听的socket添加到epoll_fd中
    if(-1 == epoll_ctl(epoll_fd,EPOLL_CTL_ADD,fd,&ev))
    {
        perror("epoll_add error");
    }
}


//阻塞等待事件
int myepoll_wait_block(struct epoll_event *events,int max_size)
{
    int num = epoll_wait(epoll_fd,events,max_size,-1);
    if(-1 == num)
    {
        
        perror("epoll_wait_block error");
        return -1;
    }
    return num;//返回继续阻塞等待
}

 
//将套接子文件描述符从epoll集合中删除
void myepoll_delete_in(int fd)
{
    //从epoll监听删除下线fd
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events  = EPOLLIN;
    if(0 != epoll_ctl(epoll_fd,EPOLL_CTL_DEL,fd,&ev))
    {
        perror("epoll_delete epoll_ctl error");
        return;
    }
}


//销毁epoll
void myepoll_destroy()
{
    if(-1 == close(epoll_fd))
    {
        perror("epoll_destroy close error");
    }
}