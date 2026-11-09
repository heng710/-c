#include <stdio.h>
#include "index.h"
book books[SIZE_M];
int xb = 0;     //书名 一本书加一 写到books数组里面记录
void book_head(){
    while (1)
    {
                printf("-------------欢迎进入图书管理系统-------------");
        printf("\n");
        printf("\n");
        printf("请输入想要选择的功能！");
        printf("\n");
        printf("1、图书管理员系统    2、读者借阅功能系统      3、退出\n");
        int num;
        scanf("%d",&num);
        switch (num)
        {
        case 1:
            admin_book();
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            printf("请输入正确选择\n");
        }
    }
}
void admin_book()
{
    char pass[10];
    printf("请输入管理员密码:");
    scanf("%s",pass);
     while (strcmp(pass, "admin") == 0) // 判断密码是否一致
    {
        admin_inter();
        
    }
    printf("密码不对自动退出\n");
    book_head();
}
book *Inition(){
    book * p=(book *)calloc(1,sizeof(book));
    if(p==NULL){
        printf("初始化顺序表失败\n");
        return NULL;
    }
    p->quantity=0;          //数量从0开始;
    p->id=0;
    return p;
}
borrower *boor_Initon(){
    borrower *p=(borrower *)calloc(1,sizeof(borrower));
    if(p==NULL){
        printf("初始化顺序表失败\n");
        return NULL;
    }
}
//图书插入
bool book_center(int id,char *buf,int num){
    //判断数组是否存满
    if(xb >= SIZE_M)
    {
        printf("图书表已满\n");
        return false;
    }

    //写入当前下标xb的位置
    books[xb].id = id;
    strcpy(books[xb].book_name, buf); //拷贝书名
    books[xb].quantity = num;

    xb++; //图书总数+1
    return true;
}

bool book_printf(){
    if(xb == 0){
        printf("里面还没有任何书籍内容\n");
        return false;
    }
    //循环：i从0到xb-1
    for(int i = 0; i < xb; i++){
        printf("id:%d  图书名称:%s 库存剩余数量:%d\n",books[i].id, books[i].book_name, books[i].quantity);
    }
    return true;
}