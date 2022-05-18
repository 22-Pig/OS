semaphore rw = 1;    //用于实现对共享文件的互斥访问
int count = 0;       //记录当前有几个读进程在访问文件
semaphore mutex = 1; //用于保证对count变量的互斥访问
semaphore w = 1;     //用于实现"写优先"

writer()
{
    while (1)
    {
        P(w);  //在无写进程请求时进入
        P(rw); //写之前加锁
        写文件...;
        V(rw); //写完了解锁
        V(w);  //恢复对共享文件的访问
    }
}

reader()
{
    while (1)
    {
        P(w);           //在无写进程请求时进入
        P(mutex);       //各读进程互斥访问count，让里面代码实现一气呵成，避免读进程之间互斥
        if (count == 0) //由第一个读进程负责
            P(rw);      //读之前加锁
        count++;        //访问文件的读进程数+1
        V(mutex);       //释放互斥变量count
        V(w);           //恢复对共享文件的访问
        读文件...;
        P(mutex);       //各读进程互斥访问count
        count--;        //访问文件的读进程数-1
        if (count == 0) //如目前已经没有读者访问文件，则释放rw,写者可以进行写操作
            V(rw);      //读完了解锁
        V(mutex);       //释放互斥变量count
    }
}