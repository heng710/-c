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




int main(){
    int fd_fb = open("/dev/fb0", O_RDWR);
    if (fd_fb < 0)
    {
        perror("open fb0 fail");
        return -1;
    }
    int fd_img = open("/mycode/2.bmp", O_RDONLY);
    if (fd_img < 0)
    {
        perror("open 2.bmp fail");
        return -1;
    }
    char arr[1024*600*4];
   lseek(fd_img, 54, SEEK_SET);
    read(fd_img, arr, sizeof(arr));
    write(fd_fb, arr, sizeof(arr));
    close(fd_fb);
    close(fd_img);
    return 0;
}