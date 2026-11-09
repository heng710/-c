// 日志|猜数字游戏
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void read_log(void)
{

    FILE *fp = fopen("/home/zhang/桌面/c.txt", "r");
    if (fp == NULL)
    {
        perror("日志文件打开失败，可能还没有游戏记录");
        return;
    }
    char buf[512];
    printf("\n========== 历史游戏日志 ==========\n");
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        printf("%s", buf);
    }
    printf("==================================\n\n");
    fclose(fp);
}
void min(FILE *fd)
{
    time_t now = time(NULL);
    struct tm *lt = localtime(&now);

    // printf("本地时间：%04d-%02d-%02d %02d:%02d:%02d\n",
    //        lt->tm_year + 1900,   // tm_year = 年份 - 1900
    //        lt->tm_mon + 1,       // tm_mon：0~11
    //        lt->tm_mday,
    //        lt->tm_hour,
    //        lt->tm_min,
    //        lt->tm_sec);
    fprintf(fd, "本地时间：%04d-%02d-%02d %02d:%02d:%02d\n",
            lt->tm_year + 1900, // tm_year = 年份 - 1900
            lt->tm_mon + 1,     // tm_mon：0~11
            lt->tm_mday,
            lt->tm_hour,
            lt->tm_min,
            lt->tm_sec);
}
int main()
{
    printf("欢迎来到猜数字游戏\n");
    srand(time(NULL));
    int random = rand() % 100 + 1;
    // printf("random = %d\n", random);

    FILE *fd = fopen("/home/zhang/桌面/c.txt", "a+");
    if (fd == NULL)
    {
        perror("fopen fail");
        return -1;
    }

    min(fd);
    fprintf(fd, "结果为: random = %d\n", random);
    int i = 10;
    while (i > 0)
    {
        min(fd);
        printf("请输入一个数字：");
        int num;
        fscanf(stdin, "%d", &num);
        if (num > 0 && num <= 100)
        {
            if (num == random)
            {
                printf("恭喜你猜对了\n");
                fprintf(fd, "恭喜你猜对了\n");
                break;
            }
            else if (num > random)
            {
                printf("你猜的数字大了\n");
            }
            else if (num < random)
            {
                printf("你猜的数字小了\n");
            }
            fprintf(fd, "你猜的%d次数字为:%d\n", 10 - i+1, num);
            i--;
        }
        else
        {
            printf("请输入一个1-100之间的数字\n");
            continue;
        }
    }
    if (i <= 0)
    {
        printf("你猜错了10次,游戏结束\n");
        fprintf(fd, "你猜错了10次,游戏结束\n");
    }
    else
    {
        printf("恭喜你猜对了,游戏结束\n");
        fprintf(fd, "你在第%d次猜对了,游戏结束\n", 10 - i);
    }
    fclose(fd);
    read_log();
    
    printf("游戏结束\n");
       return 0;
}