#include"tcp_server.h"

//创建套接字，绑定，监听
int server_create(const char *Ip,int Port)
{
    int ret;
    //创建套接字,返回一个文件描述符
    //通信域：IPv4     套接字类型：流式套接字（TCP）    附加协议：0表示不需要其他协议
    int server_socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socketfd == -1)
    {
        perror("server_socketfd is failure"); 
        exit(EXIT_ERROR);
    }
    printf("SOCKET INIT SUCCESS!\n");

    int opt = 1; //设置地址可以重复被绑定
    setsockopt(server_socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in server_addr; //定义结构体变量
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET; //采用IPv4网络协议
    server_addr.sin_addr.s_addr = inet_addr(Ip);//字符型网络地址转32位二进制数据
    server_addr.sin_port = htons(Port);//转成网络的大端序，如果主机也为大端序则不需要转

    //绑定信息，将套接字与网络信息结构体绑定
    //文件描述符    网络信息结构体    server_addr的大小
    ret = bind(server_socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret == -1)
    {
        perror("bind is failure");
        exit(EXIT_ERROR);
    }
    printf("BIND INIT SUCCESS!\n");

    //设置监听队列:将套接字设置为被动监听状态
    ret = listen(server_socketfd, LISTEN_NUM); // 10:允许同时链接的客户端的个数
    if (ret == -1)
    {
        perror("listen is failure");
        exit(EXIT_ERROR);
    }
    printf("LISTEN INIT SUCCESS!\n");
    printf("等待连接中 waiting......\n");
    
    return server_socketfd;
}

//等待链接
int server_accept(int sfd)
{
    //用于保存请求连接的用户的套接子信息：ip，port
    struct sockaddr_in client_addr;
    int addrlen = sizeof(client_addr);
    memset(&client_addr,0,addrlen);

    //阻塞等待客户端链接
    int ret = accept(sfd,(struct sockaddr*)&client_addr,&addrlen);
    if (ret == -1)
    {
        perror("server_accept is failure");
        exit(EXIT_ERROR);
    }
    printf("server_accept  SUCCESS!\n");
    printf("客户端(ip:%s | port:%d):ret = %d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),ret);
    return ret;
}

//发送
int send_msg(int cfd,const void *buf,int buf_len)
{
    int ret = send(cfd,buf,buf_len,0);
    if (ret == -1)
    {
        perror("send_msg failure");
        exit(EXIT_ERROR);
    }
    return TCP_SUCCESS;
}