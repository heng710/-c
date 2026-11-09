#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int *array;   // 数组
    int head;    // 队头
    int size;     // 队列大小
    int capacity; // 数组容量
} Queue_t, *Queue_ptr;
//初始化队列
Queue_ptr initquer(int capacity){
    Queue_ptr new=(Queue_ptr)calloc(1 ,sizeof(Queue_t));
    if(new==NULL){
        printf("内存分配失败\n");
        return NULL;
    }
    new->head=-1;
    new->size=0;
    new->capacity=5;
    new->array=(int *)calloc(capacity,sizeof(int));
    if (new->array == NULL)
    {
        printf("内存分配失败\n");
        free(new);
        return NULL;
    }
    return new;
}
int isempty(Queue_ptr s1){
    return s1->size==0;
}
int isfull(Queue_ptr s1){
    return s1->size==s1->capacity;
}
//入队
void enqueue(Queue_ptr queue, int value){
    if(isfull(queue)){
        printf("队列也满\n");
        return;
    }
    if(isempty(queue)){
        queue->head = 0;
        queue->array[0] = value;
        queue->size++;
    }else{
        int c=(queue->size+queue->head)%queue->capacity;
        queue->array[c]=value;
        queue->size++;
    }
}
//出队
int  dequeue(Queue_ptr queue){
    if(isempty(queue)){
        printf("队列为空 \n");
        return -1; 
    }
     int front = queue->array[queue->head]; // 队头元素
    queue->array[queue->head] = 0;         // 清空出队元素
    queue->head = (queue->head + 1) % queue->capacity;
    queue->size--;
    return front; 

}
//遍历
void queue_print(Queue_ptr s1){
    printf("容量:%d  现在有%d   头下标%d\n",s1->capacity,s1->size,s1->head);
    if(isempty(s1)){
        printf("队列为空 \n");
        return; 
    }
    for(int i=s1->head;i<s1->head+s1->size;i++){
        printf("%d ",s1->array[i%s1->capacity]);
    }   
    printf("\n");
    for(int i=0;i<s1->capacity;i++){
        printf("%d ",s1->array[i]);
    }
    
}

void main(){
    Queue_ptr queue=initquer(5);
    enqueue(queue,10);
    enqueue(queue,20);
    enqueue(queue,30);
    dequeue(queue);
    queue_print(queue);

}
