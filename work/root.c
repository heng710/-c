#include <stdio.h>
#include "index.h"
extern User_p user_login;   // 当前登录用户
// 管理员界面
void adminInit(Book_p book, User_p head)
{
adminInit:
    printf("请输入管理员密码(退出请输入-1): ");
    char pwd[10];
    scanf("%s", pwd);
    if (strcmp(pwd, "admin") == 0)
    {
        printf("管理员登录成功\n");
    }
    else if (strcmp(pwd, "-1") == 0)
    {
        printf("退出登录\n");
        printf("-----------------------\n\n");
        return;
    }
    else
    {
        printf("管理员登录失败，请重新输入\n");
        printf("-----------------------\n\n");
        goto adminInit;
    }
    while (1)
    {
        printf("-----------------\n");
        printf("====管理员界面====\n");
        printf("1. 图书信息录入\n");
        printf("2. 图书信息删除\n");
        printf("3. 图书信息更新\n");
        printf("4. 图书信息查询\n");
        printf("5. 修改用户信息\n");
        printf("6. 退出管理员界面\n");
        int choice;
        scanf("%d", &choice);
        while (getchar() != '\n')
            ;
        switch (choice)
        {
        case AddBook:
            add_book(book);
            break;
        case DeleteBook:
            dele_book(book);
            break;
        case UpdateBook:
            update_book(book);
            break;
        case QueryBook:
            look_up_book(book);
            break;
        case UpdateUser:
            update_user(head);
            break;
        case ExitAdmin:
            printf("退出管理员界面\n");
            return;
        default:
            printf("输入错误\n");
            break;
        }
    }
}

/*--------------------------------用户界面功能----------------------------------------------*/
// 用户界面
void user(User_p head, Book_p book, Borrow_p borrow)
{

user:
    printf("-----------------\n");
    printf("1. 用户登录账号\n");
    printf("2. 注册账号\n");
    printf("3. 退出用户界面\n");
    int c;
    scanf("%d", &c);
    while (getchar() != '\n')
        ;
    if (c == 1)
    {
        user_login = login_enable(head, book, borrow);
        if (user_login == NULL)
        {
            printf("用户登录失败\n");

            goto user;
        }
        printf("用户登录成功\n");
    }
    else if (c == 2)
    {
    sign:
        printf("注册账号\n");
        printf("退出注册请输入-1\n");
        char id[10];
        char pwd[10];
        char username[20];
        printf("请输入用户ID(4位数字): ");
        scanf("%s", id);
        if (strlen(id) != 4)
        {
            printf("用户ID格式错误,请重新输入\n");
            printf("-----------------------\n\n");
            goto sign;
        }
        if (strcmp(id, "-1") == 0)
        {
            printf("退出注册\n");
            goto user;
        }
        else if (findUser(head, id) != NULL) // 防止用户ID重复注册
        {
            printf("用户已存在，请重新输入\n");
            printf("-----------------------\n\n");
            goto sign;
        }
        printf("请输入用户密码: ");
        scanf("%s", pwd);
        printf("请输入用户名: ");
        scanf("%s", username);
        createUserList(head, id, pwd, username);
        printf("注册成功\n");
        traverseUserList(head);
        goto sign;
    }
    else if (c == 3)
    {
        printf("退出用户界面\n");
        printf("-----------------------\n\n");
        return;
    }
    else
    {
        printf("输入错误\n");
        goto user;
    }

    while (1)
    {
        printf("1. 图书信息查询\n");
        printf("2. 图书信息借阅\n");
        printf("3. 图书信息归还\n");
        printf("4. 退出用户界面\n");
        int choice;
        scanf("%d", &choice);
        while (getchar() != '\n')
            ;
        switch (choice)
        {
        case FindBook:
            traverseBookList(book);
            continue;
        case BorrowBook:
            borrow_enable(book, user_login, borrow);
            break;
        case ReturnBook:
            return_enable(book, user_login, borrow);
            break;
        case Ex:
            printf("退出用户界面\n");
            user_login = NULL;
            return;
        default:
            printf("输入错误\n");
            break;
        }
    }
}

/*--------------------------------用户界面功能----------------------------------------------*/
User_p login_enable(User_p head, Book_p book, Borrow_p borrow)
{
us:
    printf("用户登录账号\n");
    printf("退出登录请输入-1\n");
    char id[10];
    char pwd[10];
    printf("请输入用户ID: ");
    scanf("%s", id);
    if (strcmp(id, "-1") == 0)
    {
        printf("退出登录\n");
        printf("-----------------------\n\n");
        return NULL;
    }
    printf("请输入用户密码: ");
    scanf("%s", pwd);
    User_p p = findUser(head, id);
    if (p == NULL)
    {
        printf("用户不存在\n");
        printf("-----------------------\n\n");
        goto us;
    }
    if (strcmp(p->pwd, pwd) == 0)
    {
        printf("用户登录成功\n");
        return p;
    }
    else
    {
        printf("用户密码错误，请重新输入\n");
        printf("-----------------------\n\n");
        goto us;
    }
}
void borrow_enable(Book_p book, User_p head, Borrow_p borrow)
{
uu:
    printf("-----------------\n");
    printf("图书信息借阅\n");
    printf("1、查找图书ID借阅\n");
    printf("2、查找图书名称借阅\n");
    printf("3、查找图书姓名和图书名称借阅\n");
    printf("4、退出用户界面\n");
    int choice;
    scanf("%d", &choice);
    while (getchar() != '\n')
        ;
    if (choice == 1)
    {
        printf("请输入图书ID: ");
        int id;
        int ret = scanf("%d", &id);
        if (ret != 1)
        {
            printf("输入错误!ID不能是字母或字符!\n");
            // 清空缓冲区，防止死循环
            while (getchar() != '\n')
                ;
            return;
        }
        Book_p p = findBook(book, id);
        if (p == NULL)
        {
            printf("图书不存在\n");
            goto uu;
        }
        printf("图书存在\n");
        printf("图书ID: %d,图书名称: %s,作者: %s,库存数量: %d\n", p->id, p->bookname, p->author, p->remain);
        printf("是否确认借阅? (1/0): ");
        int confirm;
        scanf("%d", &confirm);
        while (getchar() != '\n')
            ;
        if (confirm == 1)
        {
            if (p->remain == 0)
            {
                printf("图书库存不足\n");
                goto uu;
            }
            else
            {
                addBorrowList(borrow, p, user_login, 1);
                printf("借阅成功\n");
                traverseBorrowList(borrow); // 遍历借阅列表
                printf("\n\n");
            }
        }
        else
        {
            printf("借阅失败\n");
            goto uu;
        }
        goto uu;
    }
    else if (choice == 2)
    {
        char bookname[40];
        printf("请输入图书名称: ");
        scanf("%s", bookname);
        while (getchar() != '\n')
            ;
        Book_p p = findBookByName(book, bookname);
        if (p == NULL)
        {
            printf("图书不存在\n");
            goto uu;
        }
        printf("图书存在\n");
        printf("图书ID: %d,图书名称: %s,作者: %s,出版年份: %d,库存数量: %d\n", p->id, p->bookname, p->author, p->year, p->remain);
        printf("是否确认借阅? (1/0): ");
        int confirm;
        scanf("%d", &confirm);
        while (getchar() != '\n')
            ;
        if (confirm == 1)
        {
            if (p->remain == 0)
            {
                printf("图书库存不足\n");
                goto uu;
            }
            else
            {
                addBorrowList(borrow, p, user_login, 1);
                printf("借阅成功\n");
                traverseBorrowList(borrow); // 遍历借阅列表
                printf("\n\n");
            }
        }
        else
        {
            printf("借阅失败\n");
        }
        goto uu;
    }
    else if (choice == 3)
    {
        char author[40];
        char bookname[40];
        printf("请输入图书姓名: ");
        scanf("%s", bookname);
        while (getchar() != '\n')
            ;
        printf("请输入图书作者: ");
        scanf("%s", author);
        while (getchar() != '\n')
            ;
        Book_p p = findBookByNameAndAuthor(book, bookname, author);
        if (p == NULL)
        {
            printf("图书不存在\n");
            goto uu;
        }

        printf("图书存在\n");
        printf("图书ID: %d,图书名称: %s,作者: %s,出版年份: %d,库存数量: %d\n", p->id, p->bookname, p->author, p->year, p->remain);
        printf("是否确认借阅? (1/0): ");
        int confirm;
        scanf("%d", &confirm);
        while (getchar() != '\n')
            ;
        if (confirm == 1)
        {
            if (p->remain == 0)
            {
                printf("图书库存不足\n");
                goto uu;
            }
            else
            {

                addBorrowList(borrow, p, user_login, 1);
                printf("借阅成功\n");
                traverseBorrowList(borrow); // 遍历借阅列表
                printf("\n\n");
            }
        }
        else
        {
            printf("借阅失败\n");
        }
        goto uu;
    }
    else if (choice == 4)
    {
        printf("退出用户界面\n");
        return;
    }
    else
    {
        printf("输入错误\n");
        goto uu;
    }
}
void return_enable(Book_p book, User_p head, Borrow_p borrow)
{
    int id;
    char bookname[40];
    printf("请输入要归还的图书ID: ");
    scanf("%d", &id);
    while (getchar() != '\n')
        ;
    printf("请输入图书名称: ");
    scanf("%s", bookname);
    while (getchar() != '\n')
        ;
    Borrow_p p = findBorrow(borrow, id);
    if (p == NULL)
    {
        printf("该用户图书未被借阅\n");
        return;
    }
    else if (strcmp(p->username, user_login->username) == 0 && strcmp(p->bookname, bookname) == 0)
    {
        Book_p q = findBook(book, id);
        q->remain++;
        p->is_return = 0;
        printf("用户ID: %d, 用户名: %s, 图书名: %s, 作者: %s, 是否归还: %d\n", p->id, p->username, p->bookname, p->author, p->is_return);
        printf("归还成功\n");

        // traverseBorrowList(borrow); // 遍历借阅列表
        printf("\n\n");
    }
    else
    {
        printf("输入错误\n");
    }
}
/*--------------------------------用户链表功能----------------------------------------------*/

// 创建用户
User_p createUser()
{
    User_p user = (User_p)malloc(sizeof(UserNode));
    if (user == NULL)
    {
        printf("内存分配失败\n");
        return NULL;
    }
    user->next = user;
    user->prev = user;
    return user;
}
// 创建用户列表
void createUserList(User_p head, const char *id, const char *pwd, const char *username)
{

    User_p p = createUser();
    strcpy(p->id, id);
    strcpy(p->pwd, pwd);
    strcpy(p->username, username);

    p->next = head->next;
    p->prev = head;
    head->next->prev = p;
    head->next = p;
}
// 遍历用户列表
void traverseUserList(User_p head)
{
    User_p p = head->next;
    while (p != head)
    {
        printf("用户ID: %s,密码: %s,用户名: %s,\n", p->id, p->pwd, p->username);
        p = p->next;
    }
}
// 查找用户账号
User_p findUser(User_p head, const char *id)
{
    User_p p = head->next;
    while (p != head)
    {
        if (strcmp(p->id, id) == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

int delete_user(User_p head)
{
    char id[10];
    printf("请输入要删除的用户ID: ");
    scanf("%s", id);
    while (getchar() != '\n')
        ;
    User_p p = findUser(head, id);
    if (p == NULL)
    {
        printf("用户不存在\n");
        return -1;
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
    // printf("删除成功\n");
    return 1;
}

/*--------------------------------管理员链表功能----------------------------------------------*/
// 图书信息初始化
Book_p addBook()
{
    Book_p book = (Book_p)malloc(sizeof(BookNode));
    if (book == NULL)
    {
        printf("内存分配失败\n");
        return NULL;
    }
    book->next = book;
    book->prev = book;
    return book;
}
// 图书信息录入
void addBookList(Book_p head, int id, const char *bookname, char *author, int year, int total, int remain)
{
    Book_p p = addBook();
    p->id = id;
    strcpy(p->bookname, bookname);
    strcpy(p->author, author);
    p->year = year;
    p->total = total;
    p->remain = remain;

    p->next = head->next;
    p->prev = head;
    head->next->prev = p;
    head->next = p;
    return;
}
// 遍历图书列表
void traverseBookList(Book_p head)
{
    Book_p p = head->next;
    while (p != head)
    {
        printf("图书ID: %d, 图书名称: %s, 作者: %s, 年份: %d, 总数量: %d, 剩余数量: %d\n", p->id, p->bookname, p->author, p->year, p->total, p->remain);
        p = p->next;
    }
}
// 查找图书ID
Book_p findBook(Book_p head, int id)
{
    Book_p p = head->next;
    while (p != head)
    {
        if (p->id == id)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
// 查找图书名称
Book_p findBookByName(Book_p head, char *bookname)
{
    Book_p p = head->next;
    while (p != head)
    {
        if (strcmp(p->bookname, bookname) == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
// 查找图书姓名和图书名称
Book_p findBookByNameAndAuthor(Book_p head, char *bookname, char *author)
{
    Book_p p = head->next;
    while (p != head)
    {
        if (strcmp(p->bookname, bookname) == 0 && strcmp(p->author, author) == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

// 图书信息删除
int delete_book(Book_p book, int id)
{
    Book_p p = findBook(book, id);
    if (p == NULL)
    {
        printf("图书ID不存在\n");
        return -1;
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
    // printf("删除成功\n");
    return 1;
}

/*--------------------------------管理员界面功能----------------------------------------------*/

void add_book(Book_p book)
{
add_book:
    printf("-----------------\n\n");
    printf("====图书信息录入====\n");
    printf("退出录入请输入-1\n");
    int id;
    char bookname[20];
    char author[20];
    int year;
    int total;
    int remain;
    printf("请输入图书ID: ");
    int ret = scanf("%d", &id);
    // while (getchar() != '\n');
    if (id == -1)
    {
        printf("退出录入\n");
        return;
    }
    if (ret != 1)
    {
        printf("输入错误!ID不能是字母或字符!\n");
        // 清空缓冲区，防止死循环
        while (getchar() != '\n')
            ;
        return;
    }
    Book_p p = findBook(book, id);
    if (p != NULL)
    {
        printf("图书ID已存在\n");
        return;
    }
    printf("请输入图书名称: ");
    scanf("%s", bookname);
    while (getchar() != '\n')
        ;
    printf("请输入作者: ");
    scanf("%s", author);
    while (getchar() != '\n')
        ;
    printf("请输入年份: ");
    scanf("%d", &year);
    while (getchar() != '\n')
        ;
    printf("请输入总数量: ");
    scanf("%d", &total);
    while (getchar() != '\n')
        ;
    printf("请输入剩余数量: ");
    scanf("%d", &remain);
    while (getchar() != '\n')
        ;
    addBookList(book, id, bookname, author, year, total, remain);
    printf("录入成功\n");
    Book_p c = findBook(book, id);
    printf("图书ID: %d, 图书名称: %s, 作者: %s, 年份: %d, 总数量: %d, 剩余数量: %d\n", c->id, c->bookname, c->author, c->year, c->total, c->remain);
    printf("-----------------\n");
    goto add_book;
}
// 图书信息删除
void dele_book(Book_p book)
{
dele_book:
    printf("-----------------\n\n");
    printf("====图书信息删除====\n");
    printf("退出删除请输入-1\n");
    int id;
    printf("请输入图书ID: ");
    scanf("%d", &id);
    while (getchar() != '\n')
        ;
    if (id == -1)
    {
        printf("退出删除\n");
        return;
    }
    Book_p p = findBook(book, id);
    if (p == NULL)
    {
        printf("图书ID不存在\n");
        goto dele_book;
    }
    else
    {
        printf("图书ID: %d, 图书名称: %s, 作者: %s, 年份: %d, 总数量: %d, 剩余数量: %d\n", p->id, p->bookname, p->author, p->year, p->total, p->remain);
        printf("确认删除吗？(1.是 2.否): ");
        int choice;
        scanf("%d", &choice);
        while (getchar() != '\n')
            ;
        if (choice == 1)
        {
            int ret = delete_book(book, id);
            if (ret == 1)
                printf("删除成功\n");
            else
            {
                printf("删除失败\n");
            }
        }
        else if (choice == 2)
        {
            printf("删除失败\n");
        }
        else
        {
            printf("输入错误\n");
        }
    }
    printf("-----------------\n");
    goto dele_book;
}
// 图书信息更新
void update_book(Book_p book)
{
update_book:
    printf("-----------------\n\n");
    printf("====图书信息更新====\n");
    printf("退出更新请输入-1\n");
    int id;
    printf("请输入图书ID: ");
    scanf("%d", &id);
    while (getchar() != '\n')
        ;
    if (id == -1)
    {
        printf("退出更新\n");
        return;
    }
    else
    {
        Book_p c = findBook(book, id);
        if (c == NULL)
        {
            printf("图书ID不存在\n");
            goto update_book;
        }
        else
        {
            printf("图书ID: %d, 图书名称: %s, 作者: %s, 年份: %d, 总数量: %d, 剩余数量: %d\n", c->id, c->bookname, c->author, c->year, c->total, c->remain);
            printf("已经查找到该图书\n");
        update:
            printf("-----------------\n\n");
            printf("1、全部更新\n");
            printf("2、部分更新\n");
            printf("3、退出更新\n");
            int choice;
            scanf("%d", &choice);
            while (getchar() != '\n')
                ;
            if (choice == 1)
            {
                delete_book(book, id);
                char bookname[20];
                char author[20];
                int year;
                int total;
                int remain;
                printf("请输入新的图书ID: ");
                scanf("%d", &id);
                while (getchar() != '\n')
                    ;
                printf("请输入新的图书名称: ");
                scanf("%s", bookname);
                while (getchar() != '\n')
                    ;
                printf("请输入新的作者: ");
                scanf("%s", author);
                while (getchar() != '\n')
                    ;
                printf("请输入新的年份: ");
                scanf("%d", &year);
                while (getchar() != '\n')
                    ;
                printf("请输入新的总数量: ");
                scanf("%d", &total);
                while (getchar() != '\n')
                    ;
                printf("请输入新的剩余数量: ");
                scanf("%d", &remain);
                while (getchar() != '\n')
                    ;
                addBookList(book, id, bookname, author, year, total, remain);
                Book_p a = findBook(book, id);
                printf("图书ID: %d, 图书名称: %s, 作者: %s, 年份: %d, 总数量: %d, 剩余数量: %d\n", a->id, a->bookname, a->author, a->year, a->total, a->remain);
                printf("更新成功\n");
            }
            else if (choice == 2)
            {
            dan:
                printf("请输入要更新的字段(1、图书ID 2、图书名称 3.作者 4.年份 5.总数量 6.剩余数量7.退出): ");
                scanf("%d", &choice);
                while (getchar() != '\n')
                    ;
                if (choice == 1)
                {
                    int cc;
                    printf("请输入图书ID: ");
                    scanf("%d", &cc);
                    while (getchar() != '\n')
                        ;
                    c->id = cc;
                    printf("更新成功\n");
                    printf("图书ID: %d, 图书名称: %s, 作者: %s, 年份: %d, 总数量: %d, 剩余数量: %d\n", c->id, c->bookname, c->author, c->year, c->total, c->remain);
                    goto dan;
                }
                else if (choice == 2)
                {
                    char bookna[40];
                    printf("请输入图书名称: ");
                    scanf("%s", bookna);
                    while (getchar() != '\n')
                        ;
                    strcpy(c->bookname, bookna);
                    printf("更新成功\n");
                    printf("图书ID: %d, 图书名称: %s, 作者: %s, 年份: %d, 总数量: %d, 剩余数量: %d\n", c->id, c->bookname, c->author, c->year, c->total, c->remain);
                    goto dan;
                }
                else if (choice == 3)
                {
                    char author[20];
                    printf("请输入作者: ");
                    scanf("%s", author);
                    while (getchar() != '\n')
                        ;
                    strcpy(c->author, author);
                    printf("更新成功\n");
                    printf("图书ID: %d, 图书名称: %s, 作者: %s, 年份: %d, 总数量: %d, 剩余数量: %d\n", c->id, c->bookname, c->author, c->year, c->total, c->remain);
                    goto dan;
                }
                else if (choice == 4)
                {
                    int cc;
                    printf("请输入年份: ");
                    scanf("%d", &cc);
                    while (getchar() != '\n')
                        ;
                    c->year = cc;
                    printf("更新成功\n");
                    printf("图书ID: %d, 图书名称: %s, 作者: %s, 年份: %d, 总数量: %d, 剩余数量: %d\n", c->id, c->bookname, c->author, c->year, c->total, c->remain);
                    goto dan;
                }
                else if (choice == 5)
                {
                    int cc;
                    printf("请输入总数量: ");
                    scanf("%d", &cc);
                    while (getchar() != '\n')
                        ;
                    c->total = cc;
                    printf("更新成功\n");
                    printf("图书ID: %d, 图书名称: %s, 作者: %s, 年份: %d, 总数量: %d, 剩余数量: %d\n", c->id, c->bookname, c->author, c->year, c->total, c->remain);
                    goto dan;
                }
                else if (choice == 6)
                {
                    int cc;
                    printf("请输入剩余数量: ");
                    scanf("%d", &cc);
                    while (getchar() != '\n')
                        ;
                    c->remain = cc;
                    printf("更新成功\n");
                    printf("图书ID: %d, 图书名称: %s, 作者: %s, 年份: %d, 总数量: %d, 剩余数量: %d\n", c->id, c->bookname, c->author, c->year, c->total, c->remain);
                    goto dan;
                }
                else if (choice == 7)
                {
                    printf("退出更新\n");
                    goto update;
                }
                else
                {
                    printf("输入错误\n");
                    goto dan;
                }
            }
            else if (choice == 3)
            {
                printf("退出更新\n");
                return;
            }
            else
            {
                printf("输入错误\n");
                goto update;
            }
        }
    }
}
void look_up_book(Book_p book)
{
    printf("-----------------\n\n");
look_up_book:
    printf("====图书信息查询====\n");
    printf("1、查询全部图书信息\n");
    printf("2、查询指定图书信息\n");
    printf("3、退出查询请输入\n");
    int choice;
    scanf("%d", &choice);
    while (getchar() != '\n')
        ;
    if (choice == 1)
    {
        traverseBookList(book);
        return;
    }
    else if (choice == 2)
    {
    feek:
        int id;
        printf("请输入要查询的图书ID: ");
        printf("(-1退出查询)\n");

        scanf("%d", &id);
        while (getchar() != '\n')
            ;
        if (id == -1)
        {
            printf("退出查询\n");
            goto look_up_book;
        }
        Book_p p = findBook(book, id);
        if (p == NULL)
        {
            printf("未找到该图书\n");
            goto feek;
        }
        else
        {
            printf("图书ID: %d, 图书名称: %s, 作者: %s, 年份: %d, 总数量: %d, 剩余数量: %d\n", p->id, p->bookname, p->author, p->year, p->total, p->remain);
            goto feek;
        }
    }
    else if (choice == 3)
    {
        printf("退出查询\n");
        return;
    }
    else
    {
        printf("输入错误\n");
        goto feek;
    }
}

void update_user(User_p head)
{
update_user:
    printf("-----------------\n\n");
    printf("====修改用户信息====\n");
    printf("1、查看所有用户信息\n");
    printf("2、修改用户信息\n");
    printf("3、退出修改\n");
    int choice;
    scanf("%d", &choice);
    while (getchar() != '\n')
        ;
    if (choice == 1)
    {
        traverseUserList(head);
        goto update_user;
    }
    else if (choice == 2)
    {
    on:
        printf("-----------------\n\n");
        printf("1、修改用户ID\n");
        printf("2、修改用户名\n");
        printf("3、修改密码\n");
        printf("4、退出修改\n");
        int choice;
        scanf("%d", &choice);
        while (getchar() != '\n')
            ;
        if (choice == 1)
        {
            char old_id[10];
            printf("请输入旧的用户ID: ");
            scanf("%s", old_id);
            while (getchar() != '\n')
                ;
            User_p p = findUser(head, old_id);
            if (p == NULL)
            {
                printf("未找到该用户\n");
                goto on;
            }
            else
            {
                printf("用户ID: %s, 用户名: %s\n 密码: %s\n", p->id, p->username, p->pwd);
                printf("请输入新的用户ID: ");
                scanf("%s", p->id);
                while (getchar() != '\n')
                    ;
                printf("修改成功\n");
                goto on;
            }
        }
        else if (choice == 2)
        {
            char old_id[10];
            printf("请输入旧的用户ID: ");
            scanf("%s", old_id);
            while (getchar() != '\n')
                ;
            User_p p = findUser(head, old_id);
            if (p == NULL)
            {
                printf("未找到该用户\n");
                goto on;
            }
            else
            {
                printf("用户ID: %s, 用户名: %s\n 密码: %s\n", p->id, p->username, p->pwd);
                printf("请输入新的用户名: ");
                scanf("%s", p->username);
                while (getchar() != '\n')
                    ;
                printf("修改成功\n");
                goto on;
            }
        }
        else if (choice == 3)
        {
            char old_id[10];
            printf("请输入旧的用户ID: ");
            scanf("%s", old_id);
            while (getchar() != '\n')
                ;
            User_p p = findUser(head, old_id);
            if (p == NULL)
            {
                printf("未找到该用户\n");
                goto on;
            }
            else
            {
                printf("用户ID: %s, 用户名: %s\n 密码: %s\n", p->id, p->username, p->pwd);
                printf("请输入新的密码: ");
                scanf("%s", p->pwd);
                while (getchar() != '\n')
                    ;
                printf("修改成功\n");
                goto on;
            }
        }
        else if (choice == 4)
        {
            printf("退出修改\n");
            goto update_user;
        }
        else
        {
            printf("输入错误\n");
            update_user(head);
            return;
        }
    }
    else if (choice == 3)
    {
        printf("退出修改\n");
        return;
    }
    else
    {
        printf("输入错误\n");
        goto update_user;
    }
}

// 借阅图书初始化
Borrow_p addBorrow()
{
    Borrow_p p = (Borrow_p)malloc(sizeof(BorrowNode));
    p->next = p;
    p->prev = p;
    p->is_return = 0;
    return p;
}
void addBorrowList(Borrow_p s, Book_p book, User_p head, int data)
{
    Borrow_p borrow = addBorrow();
    if (s->next == s)
    {
        borrow->id = book->id;
        strcpy(borrow->username, user_login->username);
        strcpy(borrow->bookname, book->bookname);
        strcpy(borrow->author, book->author);
        borrow->is_return = data;
        borrow->next = s;
        borrow->prev = s;
        s->next = borrow;
        s->prev = borrow;
        book->remain--;
        return;
    }
    borrow->id = book->id;
    strcpy(borrow->username, user_login->username);
    strcpy(borrow->bookname, book->bookname);
    strcpy(borrow->author, book->author);
    borrow->is_return = data;
    borrow->next = s->next;
    borrow->prev = s;
    s->next = borrow;
    book->remain--;
    return;
}
void traverseBorrowList(Borrow_p head)
{
    Borrow_p p = head->next;
    while (p != head)
    {
        printf("用户ID: %d, 用户名: %s, 图书名: %s, 作者: %s, 是否归还: %d\n", p->id, p->username, p->bookname, p->author, p->is_return);
        p = p->next;
    }
}
// 查找用户借阅记录
Borrow_p findBorrow(Borrow_p head, int id)
{
    Borrow_p p = head->next;
    while (p != head)
    {
        if (p->id == id)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
// 归还图书初始化