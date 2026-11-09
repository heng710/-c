#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define S_KEY 0x55

void new_user()
{
    char username[10] = {0};
    char password[10] = {0};
    printf("请输入用户名：");
    scanf("%s", username);
    while(getchar()!= '\n');
       printf("请输入密码：");
    scanf("%s", password);
    while(getchar()!= '\n');
    printf("注册成功！\n");
    int i;
    // 加密
    for (i = 0; i < strlen(username); i++)
    {
        username[i] = username[i] ^ S_KEY;
    }
    for (i = 0; i < strlen(password); i++)
    {
        password[i] = password[i] ^ S_KEY;
    }

    int fd = open("user.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0)
    {
        perror("open failed");
        return;
    }
    write(fd, username, strlen(username));
    close(fd);
    fd = open("user_password.txt", O_RDWR | O_CREAT | O_APPEND, 0666);
    if (fd < 0)
    {
        perror("open failed");
        return;
    }
    write(fd, password, strlen(password));
    close(fd);
}
int  login_user()
{
    char username[10] = {0};
    char password[10] = {0};
    printf("请输入用户名：");
    scanf("%s", username);
    while(getchar()!= '\n');
       printf("请输入密码：");
    scanf("%s", password);
    while(getchar()!= '\n');
    //printf("登录成功！\n");
    int i = 0;
    for (i = 0; i < strlen(username); i++)
    {
        username[i] = username[i] ^ S_KEY;
    }
    for (i = 0; i < strlen(password); i++)
    {
        password[i] = password[i] ^ S_KEY;
    }
    int fd = open("user.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open failed");
        return -1;
    }
    char log1[10] = {0};
    char log_ps[10] = {0};
    ssize_t rlen = read(fd, log1, sizeof(log1));
    close(fd);
    fd = open("user_password.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open failed");
        return -1;
    }
    read(fd, log_ps, sizeof(log_ps));
    close(fd);
    if (strcmp(username, log1) != 0)
    {
        printf("用户名错误！\n");
        return -1;
    }
    else if (strcmp(password, log_ps) != 0)
    {
        printf("密码错误！\n");
        return -1;
    }
    printf("登录成功！\n");
    return 0;
}

int main()
{
    while (1)
    {
        printf("1、注册用户\n");
        printf("2、登录用户\n");
        printf("3、退出系统\n");
        int choice = 0;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("注册用户\n");
            new_user();
            break;
        case 2:
            printf("登录用户\n");
            login_user();
            break;
        case 3:
            printf("退出系统\n");
            break;
        default:
            printf("输入错误\n");
            break;
        }
    }

    return 0;
}