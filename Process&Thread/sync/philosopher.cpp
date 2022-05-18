semaphore chopstick[5] = {1, 1, 1, 1, 1}; //五根筷子互斥信号量
semaphore mutex = 1;                      //设置取筷子的信号量

Pi()
{
    do
    {
        P(mutex);                  //在取筷子前获得互斥量
        P(chopstick[i]);           //取左手边的筷子
        P(chopstick[(i + 1) % 5]); //取右手边的筷子
        V(mutex);                  //释放取筷子的信号量
        eat();                     //进餐
        V(chopstick[(i + 1) % 5]); //释放右手边的筷子
        V(chopstick[i]);           //释放左手边的筷子
        think();                   //思考
    } while (1);
}
