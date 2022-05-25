#include <stdio.h>
#include <stdlib.h>

#define maxPCB 6  //最大进程数
#define maxPart 6 //最大空闲分区数
#define size 10   //不再切割剩余分区的大小

typedef struct PCB_type
{
    char name;   //进程名
    int address; //进程所占分区首地址
    int len;     //进程所占分区的长度
    int valid;   // PCB标识符（有效，无效）
} PCB;

typedef struct seqlist //进程信息队列
{
    PCB PCBelem[maxPCB]; // maxPCB为系统中允许的最多进程数
    int total;           //系统中实际的进程数
} PCBseql;
//分区类型的描述
typedef struct Partition
{
    int address; //分区起址
    int len;     //分区的长度
    int valid;   //有效标识符（有效，无效）
} Part;
//内存空闲分区表（顺序表）描述
typedef struct Partlist //空白分区链
{
    Part Partelem[maxPart]; // maxPart 为系统中可能的最多空闲分区数
    int sum;                //系统中世纪的分区数
} Partseql;
//全局变量
PCBseql *pcbl;   //进程队列指针
Partseql *partl; //空闲队列指针

void initpcb() //初始化进程表vpcbl
{
    int i;
    pcbl->PCBelem[0].address = 0;
    pcbl->PCBelem[0].len = 40;
    pcbl->PCBelem[0].name = 's';
    pcbl->PCBelem[0].valid = 1;
    pcbl->total = 0;
    for (i = 1; i < maxPCB; i++)
    {
        pcbl->PCBelem[i].name = '\0';
        pcbl->PCBelem[i].address = 0;
        pcbl->PCBelem[i].len = 0;
        pcbl->PCBelem[i].valid = 0;
    }
}
void initpart() //初始化空闲分区表vpartl
{
    int i;
    partl->Partelem[0].address = 40;
    partl->Partelem[0].len = 600;
    partl->Partelem[0].valid = 1;
    for (i = 1; i < maxPart; i++)
    {
        partl->Partelem[i].address = 0;
        partl->Partelem[i].len = 0;
        partl->Partelem[i].valid = 0;
    }
    partl->sum = 1;
}
void request(char name, int len) //进程name请求len大小的内存
{
    int i, j, k;
    int address;
    for (i = 0; i < partl->sum; i++)
    {
        if (partl->Partelem[i].len >= len)
        {
            address = partl->Partelem[i].address;
            if (partl->Partelem[i].len - len >= size)
            {
                partl->Partelem[i].address += len;
                partl->Partelem[i].len -= len;
                partl->Partelem[i].valid = 1;
            }
            else
            {
                for (j = i; j < maxPart - 1; j++)
                {
                    partl->Partelem[j] = partl->Partelem[j + 1];
                }
                partl->Partelem[j].valid = 0;
                partl->Partelem[j].address = 0;
                partl->Partelem[j].len = 0;
                partl->sum--;
            }
            for (k = 0; k < maxPCB; k++)
            {
                if (pcbl->PCBelem[k].valid == 0)
                {
                    pcbl->PCBelem[k].address = address;
                    pcbl->PCBelem[k].len = len;
                    pcbl->PCBelem[k].name = name;
                    pcbl->PCBelem[k].valid = 1;
                    pcbl->total++;
                    break;
                }
            }
            break;
        }
        else
            printf("内存紧张，暂时不予分配，请等待！");
    }
}

void release(char name) //回收name进程所占内存空间
{
    int i;
    for (i = 0; i < maxPCB; i++)
    {
        if (pcbl->PCBelem[i].name == name)
        {
            if (pcbl->PCBelem[i].valid == 0)
                printf("%c进程非运行进程，无法结束！", name);
            else
            {
                pcbl->PCBelem[i].valid = 0;
                pcbl->total--;
                partl->Partelem[partl->sum].address =
                    pcbl->PCBelem[i].address;
                partl->Partelem[partl->sum].len = pcbl->PCBelem[i].len;
                partl->Partelem[partl->sum].valid = 1;
                partl->sum++;
            }
        }
    }
}

void print() //输出内存空闲分区
{
    int i;
    printf("当前的进程有：\n");
    printf("name         address         length\n");
    for (i = 1; i < maxPCB; i++)
    {
        if (pcbl->PCBelem[i].valid == 1)
            printf("%c            %d            %d\n", pcbl->PCBelem[i].name, pcbl->PCBelem[i].address, pcbl->PCBelem[i].len);
    }
    printf("当前的空闲分区有：\n");
    printf("address      length\n");
    for (i = 0; i < maxPart; i++)
    {
        if (partl->Partelem[i].valid == 1)
            printf("%d          %d\n",
                   partl->Partelem[i].address, partl->Partelem[i].len);
    }
}

int main()
{
    char ch;
    char pcbname;
    int pcblen;
    PCBseql pcb;
    Partseql part;
    pcbl = &pcb;
    partl = &part;
    initpcb();
    initpart();
    printf("\t****************************MENU***************************\n");
    printf("\t**************       Enter: r    请求分配内存**************\n");
    printf("\t**************       Enter: s    结束进程    **************\n");
    printf("\t**************       Enter: p    打印分配情况**************\n");
    printf("\t**************       Enter: e    退出        **************\n");
    ch = getchar();
    fflush(stdin);
    while (ch != 'e')
    {
        switch (ch)
        {
        case 'r':
            printf("请输入请求进程的name，len:");

            scanf("%c %d", &pcbname, &pcblen);
            fflush(stdin);
            request(pcbname, pcblen);
            break;
        case 's':
            printf("请输入要结束进程的name：");
            scanf("%c", &pcbname);
            fflush(stdin);
            release(pcbname);
            break;
        case 'p':
            print();
            break;
        case 'e':
            exit(0);
        }
        ch = getchar();
        fflush(stdin);
    }

    return -1;
}