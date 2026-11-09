#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
} node;

node *center_data(int data)
{
    node *newnode = (node *)malloc(sizeof(node));
    if (newnode == NULL)
    {
        printf("链表申请失败");
        return NULL;
    }
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}
// 尾插
void center_tail(node **head, int data)
{
    node *newnode = center_data(data);
    if (newnode == NULL)
    {
        printf("数据传递失败\n");
        return;
    }
    if (*head == NULL)
    {
        *head = newnode;
        return;
    }
    node *p = *head;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = newnode;
}
// 头插
void center_head(node **head, int data)
{
    node *newnode = center_data(data);
    if (newnode == NULL)
    {
        printf("数据传递失败\n");
        return;
    }
    newnode->next = *head;
    *head = newnode;
}
// 遍历
void Iterate(node *head)
{
    node *p = head;

    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}
// 查找指定位置
node *find_ltcation(node *head, int data)
{
    node *p = head;
    while (p != NULL)
    {
        if (p->data == data)
        {
            return p;
        }
        p = p->next;
    };
    return NULL;
}
// 修改指定位置
void change_location(node *head, int location, int data)
{
    node *p = find_ltcation(head, location);
    if (p != NULL)
    {
        p->data = data;
    }
    else
    {
        printf("链表没有这个数据");
    }
}
// 删除
int delect_data(node **head, int data)
{
    if (*head == NULL)
    {
        printf("链表没有数据\n");
        return 0;
    }
    node *p = *head;
    node *j = NULL;
    // 头删
    if (p->data == data)
    {
        *head = p->next;
        free(p);
        return 1;
    }
    while (p != NULL && p->data != data)
    {
        j = p;
        p = p->next;
    }

    if (p == NULL)
    {
        printf("链表里面没有这个数据");
        return 0;
    }
    j->next = p->next;
    free(p);
    printf("销毁成功\n");
    return 1;
}
void main()
{
    node *head = NULL;
    center_tail(&head, 90);
    center_head(&head, 30);
    center_head(&head, 40);
    center_head(&head, 50);
    center_head(&head, 60);
    change_location(head, 30, 10);
    Iterate(head);
    delect_data(&head, 10);
    Iterate(head);
    printf("%d",head->data);
}