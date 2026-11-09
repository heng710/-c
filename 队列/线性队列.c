#include<stdio.h>
#define MAX_SIZE 6

typedef int data_int;

    
typedef struct node
{
     data_int str[MAX_SIZE];
     data_int  top;
     data_int  tail;
}node;
//初始化
void Inition(node *p){
    p->top=0;
    p->tail=0;
}
//判断队空
int isEmpty(node *p){
    return p->top==p->tail;
}
//判断队满
int isfull(node *p){
    return  (p->tail+1)%MAX_SIZE==p->top;
}
//入队
void push(node *p,data_int val){
    if(isfull(p)){
        printf("队伍已满");
    }
    p->tail=(p->tail+1)%MAX_SIZE;
    p->str[p->tail]=val;
}
//出队
int pop(node *p){
    if(isEmpty(p)){
        printf("队列为空");
        return -1;
    }
    p->top=(p->top+1)%MAX_SIZE;
    int temp=p->str[p->top];
    return temp;
}

//容量为6 但是第一个位置不能站数据 所以是5个
void test(){
    node p;
    Inition(&p);
    push(&p,10);
    push(&p,20);
    push(&p,30);
    push(&p,40);

    printf("%d  ",pop(&p));
    printf("%d",pop(&p));
    push(&p,70);
    push(&p,80);
    push(&p,90);
   // push(&p,90);
    printf("%d",pop(&p));
    push(&p,90);



}



void main(){
    test();
}