#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 函数：写日志
// fp：已经打开好的日志文件指针
// guess_num：本次用户猜的数字
// result_str：本次结果描述，比如猜大了、猜小了
void write_log(FILE *fp, int guess_num, const char *result_str)
{
    // 判断文件指针是否有效，防止空指针访问崩溃
    if (fp == NULL)
        return;

    time_t now = time(NULL);        // 获取当前系统秒数
    struct tm *t = localtime(&now); // 把秒数转成年、月、日、时、分、秒

    // 格式化写入日志，带上时间、猜测数字、结果
    fprintf(fp, "[%04d-%02d-%02d %02d:%02d:%02d] 猜测：%d  -> %s\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, guess_num, result_str);

    // 强制刷新缓冲区，把数据立刻写到磁盘
    // 标准IO自带缓冲区，不fflush，程序突然退出可能日志没保存上
    fflush(fp);
}

// 函数：读取并打印全部日志
void read_log(void)
{
    // 只读方式打开日志文件
    FILE *fp = fopen("/home/dante/gz2633", "r");
    if (fp == NULL)
    {
        perror("日志文件打开失败，可能还没有游戏记录");
        return;
    }

    // 定义缓冲区，用来存每次读到的一行内容
    char buf[512];
    printf("\n========== 历史游戏日志 ==========\n");

    // fgets一次读一行，读到文件末尾就返回NULL，循环结束
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        printf("%s", buf);
    }
    printf("==================================\n\n");

    // 用完一定要关闭文件，释放资源
    fclose(fp);
}

// 函数：开始一局猜数字游戏
// 返回值：这一局一共猜了多少次
int game_run(void)
{
    // a模式：追加写入，原来的内容不会被覆盖，新内容写在文件末尾
    FILE *fp_log = fopen("/home/dante/gz2633", "a");
    if (fp_log == NULL)
    {
        perror("打开日志失败");
        return -1;
    }

    // 记录本局游戏开始的时间，打印一条分隔线，方便区分每一局
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(fp_log, "===== 新一局开始 [%04d-%02d-%02d %02d:%02d:%02d] =====\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    fflush(fp_log);

    int ret_num, guess;
    int count = 0; // 计数器，记录猜的次数

    // 设置随机数种子，只用time，保证每次运行随机数字不一样
    srand((unsigned)time(NULL));
    ret_num = rand() % 100 + 1; // 生成1~100之间的随机数

    printf("===== 猜数字游戏（1~100）=====\n");

    while (1)
    {
        printf("请输入你猜测的数字：");
        scanf("%d", &guess);
        count++; // 每输入一次，次数加1

        if (guess > ret_num)
        {
            printf("猜大了！\n");
            write_log(fp_log, guess, "猜大了");
        }
        else if (guess < ret_num)
        {
            printf("猜小了！\n");
            write_log(fp_log, guess, "猜小了");
        }
        else
        {
            printf("恭喜，猜对了！\n");
            // 拼接字符串，把猜测次数放到日志里面
            char info[128];
            sprintf(info, "猜对，本局结束，一共猜了%d次", count);
            write_log(fp_log, guess, info);
            break; // 猜对，跳出循环，本局结束
        }
    }

    // 一局游戏结束，关闭日志文件
    fclose(fp_log);
    return count;
}

int main(void)
{
    int select;
    // 主菜单死循环，选完一个功能之后回到菜单
    while (1)
    {
        printf("\n===== 菜单 =====\n");
        printf("1. 开始游戏\n");
        printf("2. 查看历史日志\n");
        printf("3. 退出程序\n");
        printf("请选择：");
        scanf("%d", &select);

        switch (select)
        {
        case 1:
            game_run();
            break;
        case 2:
            read_log();
            break;
        case 3:
            printf("程序退出\n");
            exit(0); // 直接结束整个程序
        default:
            // 输入不是1、2、3的时候，提示输入错误
            printf("输入错误，请重新选择！\n");
            break;
        }
    }
    return 0;
}