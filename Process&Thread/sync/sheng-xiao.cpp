semaphore mutex = 1; // 互斥信号量，实现对缓冲区的互斥访问
semaphore empty = n; // 同步信号量，表示空闲缓冲区的数量
semaphore full = 0;  // 同步信号量，表示产品的数量，即非空缓冲区的数量

producer()
{
    while (1)
    {
        生产一个产品;
        P(empty); // 消耗一个空闲缓冲区
        P(mutex); // 实现互斥访问
        把产品放入缓冲区;
        V(mutex); // 实现互斥访问
        V(full);  // 增加一个产品
    }
}

consumer()
{
    while (1)
    {
        P(full); // 消耗一个产品（非空缓冲区）
        P(mutex);
        从缓冲区取出一个产品;
        V(mutex);
        V(empty); // 增加一个空闲缓冲区
        使用产品;
    }
}
