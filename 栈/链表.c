#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef int data_int;

typedef struct node
{
    data_int data;
    struct  node *next;
}node;

typedef struct hnode
{
    data_int size;       //栈中数量
    node *top;          //栈顶
}hnode;

hnode * link_center(){
    hnode *p=(hnode *)calloc(1,sizeof(hnode));
    if(p==NULL){
        printf("链表数据申请失败\n");
        return NULL;
    }
    p->size=0;
    p->top=NULL;
    return p;
}

node *center(data_int data){
    node *p=(node *)calloc(1,sizeof(node));
    if(p==NULL){
        printf("申请链表空间失败\n");
        return NULL;
    }
    p->data=data;
    p->next=NULL;
    return p;
}


//入栈
bool push(hnode *pan,data_int data){
    node *p=center(data);
    if(p==NULL){
        printf("入栈插入数据失败\n");
        return false;
    }
    if(pan->top==NULL){    //没有内容的时候
        pan->top=p;
        p->next=NULL;
        pan->size++;
        return true;
    }
    p->next=pan->top;
    pan->top=p;
    pan->size++;
    return true;

}

bool link_printf(hnode *pan){
    node *p=pan->top;
    while (p!=NULL)
    {
        printf("%d   ",p->data);
        p=p->next;
    }
    return true;
    
}

bool pop(hnode *pan){
    data_int temp;
    node *p=pan->top;


    temp=p->data;
    pan->top=p->next;
    p->next=NULL;
    free(p);

    pan->size--;
    return true;
    }
void main(){
    hnode *egg=link_center();
    push(egg,5);
    push(egg,10);
    push(egg,15);
    pop(egg);
   link_printf(egg);



}