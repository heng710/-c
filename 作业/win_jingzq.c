#include <stdio.h>
#include <stdbool.h>
char arr[3][3] = {0};
void array()
{
    printf("----+井字棋模板+----\n");
    int count = 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf(" %d  ", count);
            if (j != 2)
            {
                printf("|");
            }
            count++;
        }
        printf("\n");
        if (i != 2)
        {
            printf("----+----+----");
            printf("\n");
        }
    }
    printf("\n-------------\n");
}

void array1()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("  %c  ", arr[i][j]);
            if (j != 2)
            {
                printf("|");
            }
        }
        if (i != 2)
        {
            printf("\n");
            printf("----+----+----");
            printf("\n");
        }
    }
    printf("\n");
    printf("\n");
}

// 输入数值 花圈圈
bool input_array(int num, int count)   //num  输入的位置     count判断红蓝双方
{
    int c = count % 2;    // 判断自己还是对手
    int size = num - 1;   // 下标
    char *p = &arr[0][0]; // p[size]指针偏移获取
    if (num >= 1 && num <= 9)
    {
        if (c == 1 && p[size] == 0)
        {
            p[size] = 'x';
            return true;
        }
        else if (c == 0 && p[size] == 0)
        {
            p[size] = 'o';
            return true;
        }
        else
        {
            printf("位置已经占有,换个位置\n");
            return false;
        }
    }
    else
    {
        printf("输入非法位置\n");
        return false;
    }
}
// 判断胜负
char decide_win()
{
    // 横向判断
    for (int i = 0; i < 3; i++)
    {
        if (arr[i][0] != 0 && arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2])
        {
            return arr[i][0]; // 直接返回数据 是x还是o
        }
    }
    // 竖向判断
    for (int i = 0; i < 3; i++)
    {
        if (arr[0][i] != 0 && arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i]) // 横向判断
        {
            return arr[0][i]; // 直接返回数据 是x还是o
        }
    }
    // 斜向交叉
    if (arr[0][0] != 0 && arr[0][0] == arr[1][1] && arr[1][1] ==arr[2][2])
    {
        return arr[0][0];
    }
    //数据满了 平局
    char cc=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(arr[i][j]!=0){
                cc++;
            }
        }
    }
    if(cc==9){
        return 1;
    }

    
}

void main()
{
    int num;
    int count = 0;
    array();    //教程图
    array1();   //对战图
    while (1)
    {
        count++;  //记录次数      
        if (count % 2 == 1) // 判断输入方   1蓝方 0红方    
        {
            printf("请蓝方选择位置");
            scanf("%d", &num);
            if (input_array(num, count) == false) // 判断输入相同位置
            {
                count--;
            }
        }
        else
        {
            printf("请红方选择位置");
            scanf("%d", &num);
            if (input_array(num, count) == false)
            {
                count--;
            }
        } 
        array1();
        char win = decide_win();  
        if (win == 'x')
        {
            printf("蓝队胜利\n");
            break;
        }
        else if (win == 'o')
        {
            printf("红队胜利");
            break;
        }else if(win==1)
        {
            printf("平局");
            break;
        }
    }
}
// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
//     char arr1[32] = {"google"};
//     int num = 0;
//     int cc = strlen(arr1);
//     char arr2[32] = {0};
//     for (int i = 0; i < cc; i++)
//     {
//         int lage = 0;
//         for (int j = 0; j < cc; j++)
//         {
//             if (arr2[j] == arr1[i])
//             {
//                 lage = 1;
//                 break;
//             }
                
//         }
//         if (lage == 1)
//         {
//             continue;
//         }
//         else
//         {
//             arr2[num] = arr1[i];
//             num++;
//         }
//         arr2[num] = '\0';
//     }
//     printf("%s", arr2);
//     return 0; 
// }