semaphore chopstick[5] = {1, 1, 1, 1, 1}; //五根筷子互斥信号量
semaphoret count = 4;                     //用于控制就餐人数
cobegin
    哲学家进程i：
    While(TRUE)
{
    Think;
    P(count);                  //请求进入房间进餐 当count为0时 不能允许哲学家再进来了
    P(chopstick[i]);           //请求左手边的筷子
    P(chopstick[(i + 1) % 5]); //请求右手边的筷子
    Eat;
    V(chopstick[(i + 1) % 5]); //释放右手边的筷子
    V(chopstick[i]);           //释放左手边的筷子
    V(count);                  //退出房间释放信号量
}
coend
