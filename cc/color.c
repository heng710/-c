#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <stdlib.h>


#define GREEN   0x0000ff00 //绿色
#define BLACK   0x00000000 //黑色
#define YELLOW  0x00ffff00 //黄色
#define RED     0x00ff0000 //红色

int colorbuf[1024*600];
int main(){
    int fd = open("/dev/fb0", O_RDWR);
    if (-1 == fd)
    {
        perror("open fb0 fail");
    }
    //一秒循环一次颜色
    int cc[] = {GREEN, BLACK, YELLOW, RED}; 
    int j = 0;
    while(1)
    {
       
        for(int i=0; i<1024*600; i++)
        {
            colorbuf[i] = cc[j%4];
        }
        write(fd, colorbuf, sizeof(colorbuf));
        lseek(fd, 0, SEEK_SET);
        j++;
        sleep(1);
        
    }
    close(fd);
    return 0;


}