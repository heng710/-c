#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>

#define GREEN 0x0000ff00  // 绿色
#define BLACK 0x00000000  // 黑色
#define YELLOW 0x00ffff00 // 黄色
#define RED 0x00ff0000
int main()
{
    // 1.open fb0
    int fd = open("/dev/fb0", O_RDWR);
    if (-1 == fd)
    {
        perror("open fb0 fail");
    }
    int colorbuf[1024 * 600];
    int arr[3] = {BLACK, RED, YELLOW};
    int j = 0;
    while (1)
    {
        for (int i = 0; i < 1024 * 600; i++)
        {
            if (i < 1024 * 600 / 3)
            {
                colorbuf[i] = arr[j % 3];
                
            }
            else if (i >= 1024 * 600 / 3 && i < 1024 * 600 / 3 * 2)
            {
                colorbuf[i] = arr[(j+1) % 3];
                
            }
            else if (i >= 1024 * 600 / 3 * 2)
            {
                colorbuf[i] = arr[(j+2) % 3];
               
            }
        }
        j++;
        sleep(1);
        lseek(fd, 0, SEEK_SET);
        write(fd, colorbuf, sizeof(colorbuf));
    }
    close(fd);
    return 0;
}