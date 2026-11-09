#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *pevr;
    struct node *next;
}hnode,*pnode;
//结点
pnode  node_create(int data){
    pnode newnode=(pnode)calloc(1,sizeof(hnode));
    if(newnode==NULL){
        printf("创建链表失败\n");
        return NULL;
    }
    newnode->data=data;
    newnode->next=newnode;
    newnode->pevr=newnode;
    return  newnode;
}
//头插
int node_head(pnode p,int data){
    pnode newnode=node_create(data);
    if(newnode==NULL){
        printf("创建链表失败\n");
        return 0;
    }
    newnode->next=p->next;
    newnode->pevr=p;


    p->next->pevr=newnode;
    p->next=newnode;
}
//尾插
int node_tail(pnode p,int data){
    pnode newnode=node_create(data);
    if(newnode==NULL){
        printf("创建链表失败\n");
        return 0;
    }
     p->pevr->next=newnode;
    newnode->pevr=p->pevr;

    p->pevr=newnode;
    newnode->next=p;
    return 1;
}
//遍历
void node_printf(pnode p){
    pnode c=p->next;
    while (c!=p)
    {
        printf("%d ",c->data);
        c=c->next;
    }
    printf("\n");
}
//查找
pnode node_find(pnode p,int data){
    pnode c=p->next;
    while (c!=p)
    {
        if(c->data==data){
            printf("找到了\n");
            return c;
        }
        c=c->next;
    }
    printf("链表里面没有这个数据\n");
    return NULL;
}
//替换
pnode node_repeale(pnode p,int data,int newdata){
    pnode new=node_find(p,data);
    if(new==NULL){
        return NULL;
    }
    new->data=newdata;
    return new;
}
//插入指定位置前插入
pnode node_poil_head(pnode p,int data,int newdata){
    pnode newnode=node_create(newdata);
    pnode c=node_find(p,data);
    if(c==NULL){
        return NULL;
    }
    newnode->next=c;
    newnode->pevr=c->pevr;

    c->pevr->next=newnode;
    c->pevr=newnode;
    return newnode;
}
//插入指定位置后面
pnode node_poil_tail(pnode p,int data,int newdata){
    pnode newnode=node_create(newdata);
    pnode c=node_find(p,data);
    if(c==NULL){
        return NULL;
    }
    newnode->next=c->next;
    newnode->pevr=c;

    c->next->pevr=newnode;
    c->next=newnode;
    return newnode;
}
//删除
pnode node_delete(pnode p,int data){
    pnode c=node_find(p,data);
    if(c==NULL){
        return NULL;
    }
    c->pevr->next=c->next;
    c->next=c->pevr->next;
    return c;
}
void main(){
    pnode s1=node_create(-1);
    node_head(s1,3);
    node_head(s1,2);
    node_head(s1,1);
    node_tail(s1,10);
    node_tail(s1,20);
    node_tail(s1,40);
    node_printf(s1);
    //node_find(s1,10);
    node_repeale(s1,10,100);
    //node_printf(s1);
    //node_delete(s1,100);
    node_repeale(s1,1,50);
    node_poil_head(s1,2,20);
    node_poil_tail(s1,20,30);
    node_printf(s1);
}