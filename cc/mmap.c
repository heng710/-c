#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

#define GREEN 0x0000ff00  // 绿色
#define BLACK 0x00000000  // 黑色
#define YELLOW 0x00ffff00 // 黄色
#define RED 0x00ff0000    // 红色
#define WHITE 0x00FFFFFF  // 白色

#define W 1024
#define H 600

int canvas[W * H];
int main(void)
{
    int fd = open("/dev/fb0", O_RDWR);
    int arr[] = {BLACK, RED, YELLOW, GREEN, WHITE};
    if (fd < 0)
    {
        perror("open fb0 fail");
        return -1;
    }
    int *fbp = mmap(NULL, W * H * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (fbp == MAP_FAILED)
    {
        perror("mmap fb0 fail");
        close(fd);
        return -1;
    }
    int j = 0;
    while (1)
    {
        for (int i = 0; i < W * H ; i++)
        {
            canvas[i] = arr[j % 5];
        }
        j++;
        memcpy(fbp, canvas, W * H*4);
        sleep(1);
    }
    munmap(fbp, W * H * 4);
    close(fd);
    return 0;
}