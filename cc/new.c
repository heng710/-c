#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

#include </usr/include/linux/input.h>
#include </usr/include/linux/input-event-codes.h>
#define GREEN   0x0000ff00 //绿色
#define BLACK   0x00000000 //黑色
#define YELLOW  0x00ffff00 //黄色
#define RED     0x00ff0000 //红色

int colorbuf[1024*600];
int color[4] = {GREEN, BLACK, YELLOW, RED};
int j = 0;
void fun(int *x,int *y){
    int fd = open("/dev/input/event6",O_RDONLY);
    if(fd < 0)
    {
    printf("open event0 error!\n");
    }   
    struct input_event buf;
    while(1){
        read(fd,&buf,sizeof(buf));
        if(buf.type==EV_ABS&&buf.code==ABS_X){
               *x = buf.value;
        }
        else if(buf.type==EV_ABS&&buf.code==ABS_Y){
               *y = buf.value;
        }
        else if(buf.type==EV_KEY&&buf.code==BTN_TOUCH&&buf.value==0){
          printf("x州坐标位：%d",*x);
          printf("y州坐标位：%d",*y);
          printf("\n");
          break;    
        }
    }

}

int main(int argc,char *argv[])
{
    int x,y;
   
   while(1){
    fun(&x,&y);
     if(x>0&&x<512){
        int fd=open("/dev/fb0",O_RDWR);
        if(fd<0){
            perror("open fb0 fail");
        }

        struct fb_var_screeninfo varinfo;
        ioctl(fd, FBIOGET_VSCREENINFO, &varinfo);
        int width = varinfo.xres;
        int height = varinfo.yres;
        for(int i=0; i<width*height; i++)
        {
            colorbuf[i] = color[j%4];
        }
        write(fd, colorbuf, width*height);
        lseek(fd, 0, SEEK_SET);
        j++;
        sleep(1);
        close(fd);
    }
    else if(x>512&&x<1024){
        int fd=open("/dev/fb0",O_RDWR);
        if(fd<0){
            perror("open fb0 fail");
        }
        j--;
        if(j<0){
            j=3;
        }
        struct fb_var_screeninfo varinfo;
        ioctl(fd, FBIOGET_VSCREENINFO, &varinfo);
        int width = varinfo.xres;
        int height = varinfo.yres;
        for(int i=0; i<width*height; i++)
        {
            colorbuf[i] = color[j%4];
        }
        write(fd, colorbuf, width*height);
        lseek(fd, 0, SEEK_SET);
        
        sleep(1);
        close(fd);
    }

   }
    return 0;
}