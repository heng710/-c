#include <stdio.h>
#include <time.h>






int main(){
    time_t tloc;
    time_t t=time(&tloc);
    struct tm *times=localtime(&tloc);
    printf("当前时间是：%d年%d月%d日 %时%d分%d秒\n",1900+times->tm_year,times->tm_mon+1,times->tm_mday,times->tm_hour,times->tm_sec);
    return 0;

}   