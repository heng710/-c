#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef int data_int;

typedef struct node{
    data_int top;
    data_int data;
    data_int *stack;

}node;
//初始化
node *link_center(){
    node *p=(node *)calloc(1,sizeof(node));
    if(p==NULL){
        printf("初始化顺序表失败\n");
        return NULL;
    }

    p->stack=(data_int *)calloc(1,sizeof(data_int));
    if(p->stack==NULL){
        printf("申请元素内存失败\n");
        return NULL;
    }

    p->data=0;
    p->top=-1;  
    return p;
}
//入栈
bool input_push(node *p,data_int data){
    p->top++;
    p->stack[p->top]=data;      
}
bool link_print(node *p){
    for(int i=0;i<=p->top;i++){
        printf("%d  ",p->stack[i]);
    }
}
//出栈
bool delect(node *pan){
    data_int temp;
    temp=pan->stack[pan->top];
    pan->top--;
}

void main(){
    node *egg=link_center();
    input_push(egg,50);
    input_push(egg,40);
    input_push(egg,5);
    //delect(egg);
    link_print(egg);

}