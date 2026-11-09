#include <stdio.h>

// 管理员菜单选项
typedef enum {
    ADMIN_ADD_BOOK = 1,
    ADMIN_DEL_BOOK,
    ADMIN_RECORD,
    ADMIN_SHOW_BOOK,
    ADMIN_MODIFY_BOOK,
    ADMIN_EXIT
}AdminOpt;

// 借阅者菜单选项
typedef enum {
    USER_INPUT_INFO = 1,
    USER_BORROW_NAME,
    USER_RETURN,
    USER_LIST,
    USER_RENEW,
    USER_EXIT
}UserOpt;

// 主菜单（选管理员 / 借阅）
typedef enum{
    MENU_ADMIN = 1,
    MENU_USER,
    MENU_QUIT
}MainMenu;

int main(void)
{
    int choice;
    while(1)
    {
        // 初始化界面，打印主菜单
        printf("=====图书管理系统=====\n");
        printf("1.管理员登录\n");
        printf("2.借阅人登录\n");
        printf("3.退出系统\n");
        printf("请输入选择：");
        scanf("%d",&choice);

        switch(choice)
        {
            case MENU_ADMIN:
              //  AdminMenu();  // 进入管理员子菜单
                break;
            case MENU_USER:
                //UserMenu();   // 进入借阅子菜单
                break;
            case MENU_QUIT:
                printf("系统退出\n");
                return 0;
            default:
                printf("输入错误！重新选择\n");
                break;
        }
    }
    return 0;
}
