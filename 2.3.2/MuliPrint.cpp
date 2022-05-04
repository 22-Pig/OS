#include <iostream>
#include <pthread.h>
#include <stdio.h>

int num = 100;
pthread_mutex_t mutex; // 声明锁函数

void *tprocess1(void *args)
{
    while (num > 0)
    {
        pthread_mutex_lock(&mutex); // 将进程锁住防止其他进程争夺资源
        int i = num;
        printf("tprocess1--%d\n", i);
        i--;
        num = i;
        pthread_mutex_unlock(&mutex); // 解锁，使得其他进程来访问资源
    }
    return NULL;
}

void *tprocess2(void *args)
{
    while (num > 0)
    {
        pthread_mutex_lock(&mutex);
        int i = num;
        printf("tprocess2--%d\n", i);
        i--;
        num = i;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, const char *argv[])
{
    // 以动态方式创建互斥锁，参数attr为空(NULL)，使用默认的互斥锁属性
    pthread_mutex_init(&mutex, NULL);
    pthread_t t1; // 创建进程 1
    pthread_t t2; // 创建进程 2
    pthread_create(&t1, NULL, tprocess1, NULL);
    pthread_create(&t2, NULL, tprocess2, NULL);
    pthread_join(t1, NULL); // 关联进程 1，只有当进程 1 结束后，所有进程才能全部结束
    return 0;
}
