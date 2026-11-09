#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>



int getFileSize(FILE*fp)
{
	//1、先保存当前文件的位置
	int curPos = ftell(fp);
	//2、将文件偏移到末尾
	fseek(fp,0,SEEK_END);
	//3、获取文件大小
	int fileSize = ftell(fp);
	//4、恢复原来的位置
	fseek(fp,0,SEEK_END);
	//5、返回文件的大小
	return fileSize;
}
int main()
{
    FILE *fd = fopen("/home/zhang/桌面/a.txt", "a+");
    if (fd == NULL)
    {
        perror("fopen fail");
        return -1;
    }
    char arr[100] = {0};
    char buf[] = {"my name is zhangsan"};
    fread(arr, 1, sizeof(arr), fd);
    printf("%s", arr);


    fwrite(buf, 1, sizeof(buf), fd);
    fclose(fd);
    return 0;
}