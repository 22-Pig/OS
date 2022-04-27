#include <stdio.h>
#include <Windows.h>
#include <time.h>

// 宏定义 定义最大值为 100000
#define MAXVAL 100000

// 设置全局变量，保存运行结果
unsigned long long sum1 = 0;
unsigned long long sum2 = 0;
unsigned long long sum3 = 0;
void sumValue();

// 线程1：计算sum1 = 1+2+3+……+10000
DWORD WINAPI adder1(LPVOID threadNum)
{
    long int value = 0;
    while (1)
    {
        if (value > MAXVAL)
        {
            return 0;
        }
        sum1 = sum1 + value;
        value++;
        printf("sum1:%llu\n", sum1);
    }
    return NULL;
}

// 线程2：计算sum2 = 100001+100002+……+200000
DWORD WINAPI adder2(LPVOID threadNum)
{
    long int value = 100001;
    while (1)
    {
        if (value > MAXVAL * 2)
        {
            return 0;
        }
        sum2 = sum2 + value;
        value++;
        printf("sum2:%llu\n", sum2);
    }
    return NULL;
}

// 直接计算 sum3 = +2+3+……+200000
void sumValue()
{
    for (int i = 0; i <= MAXVAL * 2; i++)
    {
        sum3 += i;
        printf("sum3:%llu\n", sum3);
    }
}

int main(void)
{
    // 设置开始和结束时间
    time_t start, end;
    double sumTime1, sumTime2;
    int sum;

    // 开辟两个线程，分别用来分步计算
    time(&start);
    HANDLE hFirstThread = CreateThread(0, 0, adder1, 0, 0, 0);
    HANDLE hSecondThread = CreateThread(0, 0, adder2, 0, 0, 0);
    WaitForSingleObject(hFirstThread, INFINITE);
    WaitForSingleObject(hSecondThread, INFINITE);

    // 线程结束后，计算总值
    sum = sum1 + sum2;
    time(&end);

    // 统计多线程分步计算时间
    sumTime1 = end - start;

    // 单步直接计算
    time(&start);
    sumValue();
    time(&end);

    // 统计单线程直接计算时间
    sumTime2 = end - start;

    // 输出结果
    printf("多线程分步计算sumTime1:%f\n", sumTime1);
    printf("单线程直接计算sumTime2:%f\n", sumTime2);
    system("pause");
    return 0;
}
