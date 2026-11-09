// 练习：将之前触摸屏切换图片操作打印为日志显示并保存在开发板上
// （涵盖具体操作和时间，以及结果）
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <errno.h>
#include <linux/input.h>
#include <linux/input-event-codes.h>

const char *pic_name[] = {"zhaopian.bmp", "2.bmp", "4.bmp"};
int i = 0;
int x, y;
char arr[1024 * 600 * 4] = {0};
struct tm *times()
{
    time_t tloc;
    time_t t = time(&tloc);
    struct tm *ticmes = localtime(&tloc);
    // printf("当前时间是：%d年%d月%d日 %时%d分%d秒\n",1900+times->tm_year,times->tm_mon+1,times->tm_mday,times->tm_hour,times->tm_sec);
    return ticmes;
}

int send_img(int fd_fb, int i)
{
    int fd_phone = open(pic_name[i], O_RDONLY);
    if (fd_phone < 0)
    {
        perror("open zhaopian.bmp fail");
        return -1;
    }

    int *lcd_p = mmap(NULL, 1024 * 600 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb, 0);
    if (lcd_p == MAP_FAILED)
    {
        perror("mmap fail");
        return -1;
    }
    lseek(fd_phone, 54, SEEK_SET);

    read(fd_phone, arr, sizeof(arr));
    int x = 0;
    int y = 0;
    for (y = 0; y < 600; y++)
    {
        for (x = 0; x < 1024; x++)
        {
            lcd_p[1024 * (599 - y) + x] = arr[3 * (y * 1024 + x) + 2] << 16 | 
                arr[3 * (y * 1024 + x) + 1] << 8 | arr[3 * (y * 1024 + x)];
        }
    }
    munmap(lcd_p, 1024 * 600 * 4);
    close(fd_phone);
    return 0;
}

int write_img(int x, int y, char *str)
{
    struct tm *tim = times();
    FILE *fd = fopen("/mycode/b.txt", "a+");
    if (fd == NULL)
    {
        perror("fopen fail");
        return -1;
    }
    fprintf(fd, "[%d-%02d-%02d %02d:%02d:%02d] x坐标:%d, y坐标:%d, 图片:%s\n",
        1900 + tim->tm_year, tim->tm_mon + 1, tim->tm_mday,
        tim->tm_hour, tim->tm_min, tim->tm_sec, x, y, str);

    fclose(fd);
    return 0;
}

int main()
{
    int fd_lcd = open("/dev/input/event6", O_RDWR);
    if (fd_lcd < 0)
    {
        perror("open input/event0 fail");
        return -1;
    }
    int fd_fb = open("/dev/fb0", O_RDWR);
    if (fd_fb < 0)
    {
        perror("open fb0 fail");
        return -1;
    }
    struct input_event info;
    while (1)
    {
        int cc = 0;
        read(fd_lcd, &info, sizeof(info));
        if (info.type == EV_ABS)
        {
            if (info.code == ABS_X)
            {
                x = info.value;
            }
            if (info.code == ABS_Y)
            {
                y = info.value;
            }
        }

        else if (info.type == EV_KEY && info.code == BTN_TOUCH)
        {

            if (info.value == 1)
                cc = 1;
            if (cc == 1)
            {
                cc = 0;
                send_img(fd_fb, i % 3);
                write_img(x, y, (char *)pic_name[i % 3]);
                i++;
            }
        }
    }
    close(fd_lcd);
    close(fd_fb);
    return 0;
}
