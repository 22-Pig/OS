// 实现互斥访问盘子（缓冲区）
semaphore mutex = 1;
// 盘子中有几个苹果
semaphore apple = 0;
// 盘子中有几个橘子
semaphore orange = 0;
// 盘子中还可以放入多少个水果
semaphore plate = 1;

dad()
{
    while (1)
    {
        准备一个苹果;
        P(plate);
        P(mutex);
        把苹果放入盘子;
        V(mutex);
        V(apple);
    }
}

mom()
{
    while (1)
    {
        准备一个橘子;
        P(plate);
        P(mutex);
        把橘子放入盘子;
        V(mutex);
        V(orange);
    }
}

daughter()
{
    while (1)
    {
        P(apple);
        P(mutex);
        从盘子中取出苹果;
        V(mutex);
        V(plate);
        吃掉苹果;
    }
}

son()
{
    while (1)
    {
        P(orange);
        P(mutex);
        从盘子中取出橘子;
        V(mutex);
        V(plate);
        吃掉橘子;
    }
}
