#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* PCB表结构 */
typedef struct node
{
    char name;  /*进程的名字*/
    int status; /*进程的状态，W--就绪态，R--执行态，F--完成态*/
    int precendence;
    int ax, bx, cx, dx;
    int pc;
    int psw;
    struct node *next; /*链表指针*/
} pcb;

/* 函数声明 */
pcb *CreateProcess(pcb *head, int n);
void ProcessFiFo(pcb *head);

/* 创建进程 */
pcb *CreateProcess(pcb *head, int n)
{
    pcb *p, *q;
    head = (pcb *)malloc(sizeof(pcb));
    head->next = NULL;
    p = head;

    for (int i = 0; i < n; i++)
    {
        q = (pcb *)malloc(sizeof(pcb));
        printf("请输入第%d个进程名字：\n", i + 1);
        scanf("%s", &q->name);
        printf("输入进程相关数据：\n");
        scanf("%s", &q->status);
        fflush(stdin);
        // q->next = p->next;
        p->next = q;
        p = q;
    }
    return head;
}

/* FiFo调度算法 */
void ProcessFiFo(pcb *head)
{
    pcb *p;
    p = head->next;
    printf("进程运行顺序：\n");

    while (p)
    {
        printf("%s", p->name);
        printf("1");
        p = p->next;
    }
    printf("\n");
}

int main()
{
    pcb *head = NULL;
    int n;
    printf("请输入需创建进程个数：\n");
    scanf("%d", &n);
    head = CreateProcess(head, n);
    ProcessFiFo(head);
    return 0;
}