#include"tcp_client.h"

static int client_socketfd;

//连接服务器
int client_connect(const char *ip,int port)
{
    int ret;
    //创建套接字
    int client_socketfd = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == client_socketfd)
    {
        perror("socket error");
        exit(C_ERROR);
    }
    printf("SOCKET INIT SUCCESS!\n");

    //向服务器发起连接
    struct sockaddr_in server_addr; //保存服务器信息
    memset(&server_addr,0,sizeof(server_addr));//
    server_addr.sin_family = AF_INET;  //地址族 ipv4
    server_addr.sin_port = htons(port); //网络字节序端口
    server_addr.sin_addr.s_addr = inet_addr(ip);  //ip地址

    ret = connect(client_socketfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(-1 == ret)
    {
        perror("connect error");
        close(client_socketfd);
        exit(C_ERROR);
    }
    return C_FAILURE;
}

//获取服务器的socket
int get_sockfd()
{
    return client_socketfd;
}

//向服务器发送消息
int client_send(const void *buf, int buf_len)
{
    int ret = send(client_socketfd, buf, buf_len, 0);
    if(-1 == ret)
    {
        perror("client_send: send error");
        return C_FAILURE;
    }
    return C_SUCCESS;
}

//客户端接收消息
int client_recv(void *buf, int buf_len)
{
    int ret = recv(client_socketfd, buf, buf_len, 0);
    if(-1 == ret)
    {
        perror("client_recv: recv error");
        return C_FAILURE;
    }
    return C_SUCCESS; 
}

//关闭服务器socket
int client_close()
{
    if(-1 == close(client_socketfd))
    {
        perror("client_close: close");
        return C_FAILURE;
    }
    return C_SUCCESS;
}