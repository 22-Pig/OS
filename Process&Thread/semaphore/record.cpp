#include <stdio.h>
#include <stdlib.h>

/* 记录型信号量的定义 */
typedef struct
{
    int value;         // 剩余资源数
    struct process *L; // 等待队列
} semaphore;

/* 某进程需要使用资源时，通过wait原语申请 */
void wait(semaphore S)
{
    S.value--;
    if (S.value < 0)
    {
        block(S.L); // block原语阻塞队列，由于进入阻塞态，所以遵循了 让权等待
    }
}

/* 进程使用完资源后，通过signal原语释放 */
void signal(semaphore S)
{
    S.value++;
    if (S.value <= 0)
    {
        wakeup(S.L); // 唤醒等待队列中的第一个进程
    }
}