#include <stdio.h>

typedef struct
{
    char name[10];
    int age;
    int height;
} stu_t;


void send__stu(){
    printf("请输入3个学生信息:\n");
    stu_t stu[3];
    for(int i=0; i<3; i++){
        printf("请输入第%d个学生的姓名:", i + 1);
        scanf("%s", stu[i].name);
        printf("请输入第%d个学生的年龄:", i + 1);
        scanf("%d", &stu[i].age);
        printf("请输入第%d个学生的身高:", i + 1);
        scanf("%d", &stu[i].height);
    }
    FILE *fd=fopen("/home/zhang/桌面/b.txt", "a+");
    if(fd==NULL){
        perror("fopen fail");
        return ;
    }
    for(int i=0; i<3; i++){
        fprintf(fd, "姓名：%s 年龄：%d 身高：%d\n", stu[i].name, stu[i].age, stu[i].height);  
    }
    fclose(fd);
    return ;
}

void receive__stu(){
    FILE *fd=fopen("/home/zhang/桌面/b.txt", "a+");
    if(fd==NULL){
        perror("fopen fail");
        return;
    }
    char arr[500]={0};
    fseek(fd, 0, SEEK_SET);
    fread(arr, 1, sizeof(arr), fd);
    printf("%s", arr);
    fclose(fd);
}
int main()
{
    //send__stu();
    receive__stu();
}
