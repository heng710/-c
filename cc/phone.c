#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
int main()
{
    int fd_lcd = open("/dev/fb0", O_RDWR);
    if (fd_lcd < 0)
    {
        perror("open fb0 fail");
    }
    int fd_phone = open("/mycode/2.bmp", O_RDONLY);
    if (fd_phone < 0)
    {
        perror("open zhaopian.bmp fail");
    }

    int *lcd_p = mmap(NULL, 1024 * 600 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_lcd, 0);
    if (lcd_p == MAP_FAILED)
    {
        perror("mmap fail");
        return -1;
    }
    
    lseek(fd_phone, 54, SEEK_SET);
    char arr[1024 * 600 * 4] = {0};

    read(fd_phone, arr, sizeof(arr));

    int x = 0;
    int y = 0;
    for (y = 0; y < 600; y++)
    {
        for (x = 0; x < 1024; x++)
        {
            lcd_p[1024 * (599 - y) + x] = arr[3 * (y * 1024 + x) + 2] << 16 | arr[3 * (y * 1024 + x) + 1] << 8 | arr[3 * (y * 1024 + x)];
        }
    }
    munmap(lcd_p, 1024 * 600 * 4);
    close(fd_lcd);
    close(fd_phone);
    return 0;
}
