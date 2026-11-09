#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef int  data_int;

typedef struct node{
    data_int data;      //存放数据
    struct node *next;  //下一个数据
    struct node *prev;  //返回指向
}node;

node *center(){
    node *p=(node *)calloc(1,sizeof(node));
    if(p==NULL){
        printf("申请空间失败\n");
        return NULL;
    }
    p->next=p;
    p->prev=p;
    return p;
}
//尾插
bool input_tail(node *pan,data_int data){
    node *p=(node *)calloc(1,sizeof(node));
    if(p==NULL){
        printf("申请链表为空\n");
        return false;
    } 
    p->next=pan;
    p->prev=pan->prev;
    p->data=data;

    
    
    pan->prev->next = p;
    pan->prev = p;
    return true;
}
//头插
bool input_head(node *pan,data_int data){
    node *p=(node *)calloc(1,sizeof(node));
    if(p==NULL){
        printf("申请链表为空\n");
        return false;
    } 
    p->data=data;
    p->next=pan->next;
    p->prev=pan;

    pan->next->prev=p; 
    pan->next=p;
    
    

}
//遍历
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
//删除
bool input_delect(node *pan,data_int data){
    data_int temp;
    node *p=pan->next;
    int c=1;
    while(p!=pan){
        if(p->data==data){
            p->prev->next=p->next;
            p->next->prev=p->prev;
            p->data=temp;
            free(p);
            printf("数据在第%d个,已经删除\n",c);
            return true;
        }
	c++;
        p=p->next;
    }
    printf("数据没在链表中");
    return false;


}
void main(){
    node *egg=center();
    input_tail(egg,50);
    input_tail(egg,40);
    input_tail(egg,30);
    input_head(egg,20);
    input_head(egg,15);
    input_head(egg,5);
    input_delect(egg,52);
    input_prinf(egg);


}
