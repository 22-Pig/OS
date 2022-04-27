#include <stdio.h>
#include <Windows.h>
#include <time.h>
#define MAXVAL 100000
unsigned long long sum1 = 0;
unsigned long long sum2 = 0;
unsigned long long sum3 = 0;
void sumValue();

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

DWORD WINAPI adder2(LPVOID threadNum)
{
    long int value = 10001;
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
    time_t start, end;
    double sumTime1, sumTime2;
    int sum;
    time(&start);
    HANDLE hFirstThread = CreateThread(0, 0, adder1, 0, 0, 0);
    HANDLE hSecondThread = CreateThread(0, 0, adder2, 0, 0, 0);
    WaitForSingleObject(hFirstThread, INFINITE);
    WaitForSingleObject(hSecondThread, INFINITE);
    sum = sum1 + sum2;
    time(&end);
    sumTime1 = end - start;
    time(&start);
    sumValue();
    time(&end);
    sumTime2 = end - start;
    // printf("sum1:%llu\n",sum);
    // printf("sum2:%llu\n",sum3);
    printf("sumTime1:%f\n", sumTime1);
    printf("sumTime2:%f\n", sumTime2);
    system("pause");
    return 0;
}
