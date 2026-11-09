#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define RED     0xFF0000
#define BLACK   0x000000
#define WHITE   0xFFFFFF
#define W 1024
#define H 600

int buf[W * H] = {0};

int main(void)
{
    int fd = open("/dev/fb0", O_RDWR);
    if(fd < 0)
    {
        perror("open fb0 fail");
        return -1;
    }

    // 圆心：屏幕中间，半径60
    int cx = W / 2;
    int cy = H / 2;
    int r  = 100;

    // 先清屏全黑
    memset(buf, 0, sizeof(buf));

    // 遍历所有像素，判断是不是在圆内
    for(int y = 0; y < H; y++)
    {
        for(int x = 0; x < W; x++)
        {
            int dx = x - cx;
            int dy = y - cy;
            if(dx*dx + dy*dy <= r*r)
            {
                buf[y * W + x] = RED;
            }
            else{
                buf[y * W + x] = WHITE;
            }
        }
    }

    write(fd, buf, sizeof(buf));
    close(fd);
    return 0;
}
