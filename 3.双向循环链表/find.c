#include<stdio.h>
#include "index.h"


node *center_link(){
    node *head = (node*)calloc(1,sizeof(node));
    head->prev = head;
    head->next = head;
    return head;
}   

//头
bool input_head(node *head,data_int data){
    node *p=(node *)calloc(1,sizeof(node));
    if(p==NULL){
        printf("申请链表为空\n");
        return false;
    } 
    p->data=data;
    p->next=head->next;
    p->prev=head;

    p->next->prev=p;
    head->next=p;
    return true;
}
//尾
bool input_tail(node *head,data_int data){
    node *p=(node *)calloc(1,sizeof(node));
    if(p==NULL){
        printf("申请链表为空\n");
        return false;
    } 
    node *tila =head->prev;
    p->next=head;
    p->data=data;
    p->prev=tila;

    tila->next=p;
    head->prev=p;
    return true;
}
//遍历输出
bool input_prinf(node *head){
    if(head==NULL){
        printf("链表内容为空\n");
        return false;
    }
    node *p=head->next;
    while(p!=head){
        printf("%d   ",p->data);
        p=p->next;
    }
    printf("\n");
    return true;
}
//删除指定元素
bool delect(node *head,data_int data){
    if(head==NULL||head->next==head){
        printf("数据内容为空");
        return false; 
    }
    int count=0;
    node *p=head->next;
    while(p!=head){
        count++;
        if(p->data==data){
            p->next->prev=p->prev;
            p->prev->next=p->next;
            printf("位置原来在第%d位,数据已删除\n",count);
            return true;
            
        }
        p=p->next;
    }
    printf("数据没在链表里面\n");
    return false;
}


