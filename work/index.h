#ifndef INDEX_H
#define IMDEX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum Role // 用户角色
{
    Admin = 1,
    User,
    Exit
};
enum AdminChoice // 管理员操作
{
    AddBook = 1, // 图书信息录入
    DeleteBook,  // 图书信息删除
    UpdateBook,  // 图书信息更新
    QueryBook,   // 图书信息查询
    UpdateUser,  // 修改用户信息
    ExitAdmin    // 退出管理员界面
};
enum UserChoice // 用户操作
{
    FindBook = 1, // 图书信息查询
    BorrowBook,   // 图书信息借阅
    ReturnBook,   // 图书信息归还
    Ex,           // 退出用户界面
};
typedef struct UserNode // 用户节点
{
    char id[10];
    char pwd[10];
    char username[20];
    struct UserNode *next;
    struct UserNode *prev;
} UserNode, *User_p;

typedef struct BookNode // 图书节点
{
    int id;
    char bookname[40];
    char author[20];
    int year;
    int total;  // 总数量
    int remain; // 剩余数量
    struct BookNode *next;
    struct BookNode *prev;
} BookNode, *Book_p;

typedef struct BorrowNode // 借阅节点
{
    int id;
    char username[20];
    char bookname[40];
    char author[20];
    int is_return; // 是否已归还
    struct BorrowNode *next;
    struct BorrowNode *prev;
} BorrowNode, *Borrow_p;


User_p login_enable(User_p head, Book_p book, Borrow_p borrow);
void user(User_p head, Book_p book, Borrow_p borrow);// 用户界面
int zhuce(User_p head);// 注册用户
void borrow_enable(Book_p book, User_p head, Borrow_p borrow); // 图书信息借阅
void return_enable(Book_p book, User_p head, Borrow_p borrow); // 图书信息归还


// 创建用户列表
User_p createUser(); // 创建用户列表
void createUserList(User_p head, const char *id, const char *pwd, const char *username);
void traverseUserList(User_p head);           // 遍历用户列表
User_p findUser(User_p head, const char *id); // 查找用户
int delete_user(User_p head);                 // 删除用户

// 管理员界面
void adminInit(Book_p book, User_p head); // 初始化管理员界面
void add_book(Book_p book);               // 图书信息录入
void dele_book(Book_p book);              // 图书信息删除
void update_book(Book_p book);            // 图书信息更新
void look_up_book(Book_p book);           // 图书信息查询
void update_user(User_p head);            // 修改用户信息


// 图书信息初始化
Book_p addBook(); // 初始化图书列表
void addBookList(Book_p head, int id, const char *bookname, char *author, int year, int total, int remain);
void traverseBookList(Book_p head);   // 遍历图书列表
Book_p findBook(Book_p head, int id); // 查找图书
Book_p findBookByName(Book_p head,  char *bookname); // 查找图书
Book_p findBookByNameAndAuthor(Book_p head,  char *bookname, char *author); // 查找图书
int delete_book(Book_p book, int id); // 图书信息删除


// 借阅图书初始化
Borrow_p addBorrow(); // 初始化借阅图书列表
void addBorrowList(Borrow_p s, Book_p book,User_p head,  int data); // 添加借阅图书
void traverseBorrowList(Borrow_p head); // 遍历借阅图书列表
Borrow_p findBorrow(Borrow_p head, int id); // 查找借阅图书

#endif