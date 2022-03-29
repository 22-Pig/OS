#include "iostream"
#include <windows.h>
using namespace std;

/* PCB表结构 */
typedef struct node
{
    char name;
    int status;
    int precendence;
    int ax, bx, cx, dx;
    int pc;
    int psw;
    struct node *next;
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
        cout << "请输入第" << i + 1 << "个进程名字：";
        cin >> q->name;
        cout << "输入进程相关数据：";
        cin >> q->status;
        fflush(stdin);
        q->next = p->next;
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
    cout << "进程运行顺序：";

    while (p)
    {
        cout << p->name;
        p = p->next;
    }
    printf("\n");
}

int main()
{
    pcb *head = nullptr;
    int n;
    cout << "请输入需创建进程个数：";
    cin >> n;
    head = CreateProcess(head, n);
    ProcessFiFo(head);
    return 0;
}