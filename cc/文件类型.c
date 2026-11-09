#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s filename\n", argv[0]);
        return -1;
    }
    struct stat info;
    stat(argv[1], &info);
    if (S_ISREG(info.st_mode))
    {
        printf("是普通文件\n");
        FILE *fd = fopen(argv[1], "a+");
        if (fd == NULL)
        {
            perror("fopen fail");
            return -1;
        }
        fseek(fd, 0, SEEK_END);
        char buf[] = {"hello world"};
        fprintf(fd, "%s", buf);
        fclose(fd);
    }
    else if (S_ISDIR(info.st_mode))
    {
        printf("是目录文件\n");
    }
    else
    {
        printf("未知文件类型\n");
    }
}