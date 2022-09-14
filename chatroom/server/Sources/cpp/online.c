#include "online.h"

static ol_t *ol = NULL;//头指针指向NULL

//创建在线用户链表
int ol_create()
{
    ol=(ol_t*)malloc(sizeof(ol_t));
    if(NULL == ol)
    {
        perror("ol-create:malloc error");
        return OL_FAILURE;
    }
    //初始化
    ol->count = 0;
    //带头节点
    ol->ol_head=(online_t*)calloc(1,sizeof(online_t));
    if(NULL == ol->ol_head)
    {
        perror("ol-create: calloc error");
        return OL_FAILURE;
    }
    ol->ol_head->next=NULL;
    return OL_SUCCESS;
}

//头插法插入一个在线用户
int ol_insert_head(int cfd, const char *user_id, const char *nickname, int ban, int vip)
{
    printf("user: %d | %s | %s | %d | %d\n", cfd, user_id, nickname, ban, vip);
    //初始化一个在线用户
    online_t *tmp=(online_t*)malloc(sizeof(online_t));
    if(NULL == tmp)
    {
        perror("ol_insert_head: user_id invalid argment");
        return OL_FAILURE;
    }
    tmp->cfd=cfd;
    strcpy(tmp->id, user_id);
    strcpy(tmp->nickname, nickname);
    tmp->ban = ban;
    tmp->vip = vip;
    tmp->next = NULL;
    //头插
    tmp->next = ol->ol_head->next;
    ol->ol_head->next = tmp;
    ol->count++;    //在线人数+1
    return OL_SUCCESS;
}

//通过用户Id查询在线用户
online_t *ol_query_byid(char *user_id)
{
    online_t *p=ol->ol_head->next;
    while(p)
    {
        if(0 == strcmp(user_id, p->id))
        {
            return p;    
        }
        p = p->next;
    }
    return NULL;
}

//通过客户端cfd查询在线用户
online_t *ol_query_bycfd(int cfd)
{
    //p指向头结点后的第一节点
    online_t *p = ol->ol_head->next;
    while(p)
    {
        if(cfd == p->cfd)
        {
            return p;    
        }
        p = p->next;
    }
    return NULL;
}

//通过Id从在在线用户链表删除一个下线用户
int ol_delete_bycfd(int cfd)
{
    //p指向头结点
    online_t *p=ol->ol_head;
    while(p->next)
    {
        if(cfd == p->next->cfd)
        {
            //删除节点
            online_t *tmp = p->next;
            p->next = tmp->next;
            //释放空间
            free(tmp);
            tmp = NULL;
            //在线人数-1
            ol->count--;    
            return OL_SUCCESS;
        }
        p = p->next;
    }
    return OL_FAILURE;
}

//销毁链表
void ol_destroy()
{
    //释放在线链表所有节点，p指向头节点
    online_t *p = ol->ol_head;
    online_t *tmp=NULL;
    while(p)
    {
        tmp=p;
        p=p->next;

        //释放节点
        free(tmp);
        tmp=NULL;
    }
    //释放ol
    free(ol);
    ol=NULL;
}

//返回在线链表
ol_t *get_ol()
{
    return ol;
}