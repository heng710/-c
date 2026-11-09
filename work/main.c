#include <stdio.h>
#include "index.h"

User_p user_login = NULL;
void main()
{
    User_p head = createUser();
    createUserList(head, "1001", "123456", "张三");
    createUserList(head, "1002", "654321", "李四");
    createUserList(head, "1003", "123456", "王五");
    // traverseUserList(head);
    Book_p book = addBook();
    addBookList(book, 5001, "西游记", "吴承恩", 2023, 10, 5);
    addBookList(book, 5002, "水浒传", "施耐庵", 2023, 10, 5);
    addBookList(book, 5003, "三国演义", "罗贯中", 2023, 10, 5);
    addBookList(book, 5004, "红楼梦", "曹雪芹", 2023, 10, 5);
    addBookList(book, 5005, "西游记", "曹雪芹", 2023, 10, 5);

    Borrow_p borrow = addBorrow();
    // traverseBookList(book);//遍历图书列表
    while (1)
    {
        printf("====欢迎使用图书馆管理系统====\n");
        printf("1. 管理员登录\n");
        printf("2. 用户登录\n");
        printf("3. 退出系统\n");
        int choice;
        scanf("%d", &choice);
        while (getchar() != '\n')
            ;
        switch (choice)
        {
        case Admin:
            printf("管理员登录\n");
            adminInit(book, head);
            break;
        case User:
            printf("用户登录\n");
            user(head, book, borrow);
            break;
        case Exit:
            printf("退出系统成功\n");
            return;
        default:
            printf("输入错误\n");
            break;
        }
    }
}