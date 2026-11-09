#ifndef INDEX_H
#define INDEX_H

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef int data_int;

typedef struct node{
    data_int data;
    struct node *prev;
    struct node *next;
} node;


node *center_link();

bool input_head(node *head,data_int data);

bool input_tail(node *head,data_int data);

bool input_prinf(node *head);

bool delect(node *head,data_int data);

#endif
