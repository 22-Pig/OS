#include <stdio.h>
#include <stdlib.h>

int S = 1; // 一台打印机
void wait(int S)
{
    while (S <= 0)
        ;

    S = S - 1;
}

void signal(int S)
{
    S = S + 1;
}
//进程
... wait(S); // P操作
//使用打印机
signal(S); // V操作
