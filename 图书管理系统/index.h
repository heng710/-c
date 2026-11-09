#ifndef INDEX_H
#define INDEX_H

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#define  SIZE_M 50
//管理员
typedef struct book{
    int   id;           //图书编号
    char  book_name[50];    //书名
    int   quantity;     //数量
}book;


typedef struct borrower{
    char name[20];
    char borr_book[50];
    int  isReturn;      //记录书否返书
}borrower;
extern struct book books[SIZE_M];
extern int xb;
book *Inition();  //初始化book结构体
borrower *boor_Initon();    //初始化borrower结构体
void book_head();           //第一界面
void  admin_book();         //管理员界面外层    
void admin_inter();         //管理员内层
void admin_center();        //管理层插入页面
bool book_center(int id,char *buf,int num);
bool book_printf();         //管理员查看书籍内容


#endif