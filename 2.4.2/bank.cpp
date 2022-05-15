#include <stdio.h>
#include <stdlib.h>

#define M 4 //进程数
#define N 3 //资源种类数

int available[3] = {0, 0, 0};                                        //各进程可利用的资源情况
int max[4][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};        //各进程最大需求的资源情况
int allocation[4][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}; //各进程已经分配的资源情况
int need[4][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};       //各进程仍需要的资源情况
int request[3] = {0, 0, 0};                                          //某进程请求的资源情况

/***************输入初始的资源状况***************/
void input()
{
    int i = 0, j = 0;
    printf("\t\t\t\tA  B  C\n");
    printf("请输入进程0对3类资源的最大需求:");
    for (j = 0; j < 3; j++)
    {
        scanf("%d", &max[0][j]);
    }
    printf("\n");
    printf("请输入进程1对3类资源的最大需求:");
    for (j = 0; j < 3; j++)
    {
        scanf("%d", &max[1][j]);
    }
    printf("\n");
    printf("请输入进程2对3类资源的最大需求:");
    for (j = 0; j < 3; j++)
    {
        scanf("%d", &max[2][j]);
    }
    printf("\n");
    printf("请输入进程3对3类资源的最大需求:");
    for (j = 0; j < 3; j++)
    {
        scanf("%d", &max[3][j]);
    }
    printf("\n");
    printf("请输入进程0已分配的3类资源量:");
    for (j = 0; j < 3; j++)
    {
        scanf("%d", &allocation[0][j]);
    }
    printf("\n");
    printf("请输入进程1已分配的3类资源量:");
    for (j = 0; j < 3; j++)
    {
        scanf("%d", &allocation[1][j]);
    }
    printf("\n");
    printf("请输入进程2已分配的3类资源量:");
    for (j = 0; j < 3; j++)
    {
        scanf("%d", &allocation[2][j]);
    }
    printf("\n");
    printf("请输入进程3已分配的3类资源量:");
    for (j = 0; j < 3; j++)
    {
        scanf("%d", &allocation[3][j]);
    }
    printf("\n");
    printf("请输入可利用的3类资源量:");
    for (j = 0; j < 3; j++)
    {
        scanf("%d", &available[j]);
    }
    for (i = 0; i < 4; i++)
        for (j = 0; j < 3; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    printf("\n");
}
/***************显示当前的资源状况***************/
void output()
{
    int i = 0, j = 0;
    printf("该时刻3类资源的分配情况如下:\n");
    printf("\tMAX\t\tALOCAT\t\tNEED\t\tAVAILABLE\n");
    printf("进程0:\t");
    for (j = 0; j < 3; j++)
    {
        printf("%d  ", max[0][j]);
    }
    printf("\t");
    for (j = 0; j < 3; j++)
    {
        printf("%d  ", allocation[0][j]);
    }
    printf("\t");
    for (j = 0; j < 3; j++)
    {
        printf("%d  ", need[0][j]);
    }
    printf("\t");
    for (j = 0; j < 3; j++)
    {
        printf("%d  ", available[j]);
    }
    printf("\n");
    printf("进程1:\t");
    for (j = 0; j < 3; j++)
    {
        printf("%d  ", max[1][j]);
    }
    printf("\t");
    for (j = 0; j < 3; j++)
    {
        printf("%d  ", allocation[1][j]);
    }
    printf("\t");
    for (j = 0; j < 3; j++)
    {
        printf("%d  ", need[1][j]);
    }
    printf("\n");
    printf("进程2:\t");
    for (j = 0; j < 3; j++)
    {
        printf("%d  ", max[2][j]);
    }
    printf("\t");
    for (j = 0; j < 3; j++)
    {
        printf("%d  ", allocation[2][j]);
    }
    printf("\t");
    for (j = 0; j < 3; j++)
    {
        printf("%d  ", need[2][j]);
    }
    printf("\n");
    printf("进程3:\t");
    for (j = 0; j < 3; j++)
    {
        printf("%d  ", max[3][j]);
    }
    printf("\t");
    for (j = 0; j < 3; j++)
    {
        printf("%d  ", allocation[3][j]);
    }
    printf("\t");
    for (j = 0; j < 3; j++)
    {
        printf("%d  ", need[3][j]);
    }
    printf("\n");
}
/***************给某进程分配资源***************/
void change(int n)
{
    int j;
    for (j = 0; j < N; j++)
    {
        available[j] = available[j] - request[j];
        allocation[n][j] = allocation[n][j] + request[j];
        need[n][j] = need[n][j] - request[j];
    }
}
/***************找出占用资源最多的进程***************/
int findmany()
{
    int i = 0, j = 0, k = 0, l = 0;
    i = allocation[0][0] + allocation[0][1];
    i += allocation[0][2];
    j = allocation[1][0] + allocation[1][1];
    j += allocation[1][2];
    k = allocation[2][0] + allocation[2][1];
    k += allocation[2][2];
    l = allocation[3][0] + allocation[3][1];
    l += allocation[3][2];
    if (i >= j)
    {
        if (i >= k)
        {
            if (i >= l)
                return 0;
            else
                return 3;
        }
        else
        {
            if (k >= l)
                return 2;
            else
                return 3;
        }
    }
    else
    {
        if (j >= k)
        {
            if (j >= l)
                return 1;
            else
                return 3;
        }
        else
        {
            if (k >= l)
                return 2;
            else
                return 3;
        }
    }
}
/***************找出需要资源最少的进程***************/
int findfew()
{
    int i = 0, j = 0, k = 0, l = 0;
    i = need[0][0] + need[0][1];
    i += need[0][2];
    j = need[1][0] + need[1][1];
    j += need[1][2];
    k = need[2][0] + need[2][1];
    k += need[2][2];
    l = need[3][0] + need[3][1];
    l += need[3][2];
    if (i <= j)
    {
        if (i <= k)
        {
            if (i <= l)
                return 0;
            else
                return 3;
        }
        else
        {
            if (k <= l)
                return 2;
            else
                return 3;
        }
    }
    else
    {
        if (j <= k)
        {
            if (j <= l)
                return 1;
            else
                return 3;
        }
        else
        {
            if (k <= l)
                return 2;
            else
                return 3;
        }
    }
}
/***************安全性检测***************/
int checksafe(int n)
{
    int work[3], finish[M], que[M];
    int i = 0, k = 0;
    for (i = 0; i < M; i++)
        finish[i] = false;
    for (;;)
    {
        work[0] = available[0];
        work[1] = available[1];
        work[2] = available[2];
        i = n;
        while (i < M)
        {
            if (finish[i] == false && need[i][0] <= work[0] && need[i][1] <= work[1] && need[i][2] <= work[2])
            {
                work[0] += allocation[i][0];
                work[1] += allocation[i][1];
                work[2] += allocation[i][2];
                finish[i] = true;
                que[k] = i;
                k++;
                i = 0;
            }
            else
                i++;
        }
        for (i = 0; i < M; i++)
            if (finish[i] == false)
            {
                printf("存在死锁！\n");
                return 1;
            }
        // break;
        if (finish[i] == true)
            printf("检测结果:不存在死锁！\n");
        printf("安全序列为:");
        for (i = 0; i < M; i++)
            printf("%d\t", que[i]);
        printf("\n");
        return 0;
    }
    /*printf("\n");
    printf("检测结果:不存在死锁！\n");
    printf("安全序列为:");
    for (i = 0; i<M; i++)
        printf("%d\t", que[i]);
    printf("\n");
    return 0;*/
}
/***************主函数***************/
int main()
{
    int m = 0, n = 0, i = 0, j = 0;
    printf("\t\t\t死锁的检测与解除\n");
    printf("\n");
    input();
    output();
    // enter1:
    //	{
    printf("请输入请求资源的进程号:");
    scanf("%d", &n);
    printf("\n");
//	    if(n<0||n>=M)
//		{
//			printf("您输入的进程号不存在，请重新输入！\n");
//			goto enter1;
//		}
//	}
enter2:
{
    printf("请输入进程%d对3类资源的需求量:", n);
    for (j = 0; j < 3; j++)
    {
        scanf("%d", &request[j]);
        if (request[j] > need[n][j])
        {
            printf("申请的资源数量大于自身需求的最大值！请重新输入！\n");
            goto enter2;
        }
        else
        {
            if (request[j] > available[j])
            {
                printf("申请的资源数量大于可用的资源数量！请重新输入！\n");
                goto enter2;
            }
        }
    }
}
    printf("\n");
    change(n);
    if (checksafe(n))
    {
    check:
    {
        m = findmany();
        printf("\n");
        printf("撤销进程%d所占用的资源！\n", m);
        for (j = 0; j < 3; j++)
        {
            available[j] += allocation[m][j];
            need[m][j] += allocation[m][j];
            allocation[m][j] = 0;
        }
        n = findfew();
        for (j = 0; j < 3; j++)
        {
            request[j] = need[n][j];
        }
        change(n);
        if (checksafe(n))
            goto check;
    }
    }
    output();
    system("pause");
}
