#include <stdio.h>
#include "index.h"



void admin_inter(){
    printf("\n-----欢迎来到管理员界面------\n");
        printf("1、图书录入\n");
        printf("2、图书删除\n");
        printf("3、借阅记录\n");
        printf("4、浏览图书信息\n");
        printf("5、更改图书信息\n");
        printf("6、退出\n");
        int inser;
        scanf("%d",&inser);
        switch(inser){
            case 1: admin_center();break;
            case 2:break;
            case 3:break;
            case 4:book_printf();break;
            case 5:break;
            case 6: book_head();break;
            default:printf("请输入正确的选择\n");
        }
}
void admin_center(){
    while(1){
        printf("请输入对应书籍的编号、书名、数量\n");
        printf("退出请输入-1 -1 -1\n");
        int is_id,is_num;
        char  cha;
        scanf("%d",&is_id);      
        if(is_id==-1){
            admin_inter();
            break;
        }
        scanf("%s %d",&cha,&is_num);
        book_center(is_id,&cha,is_num);
        //book_printf();
    }
   
}
void admin_delect(){
    printf("请输入你想删除的书籍id:");
    
}