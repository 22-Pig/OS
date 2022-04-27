#include <windows.h>
#include <stdio.h>
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
    printf("sub thread started\n");
    printf("sub thread finished\n");
    return 0;
}
int main(int argc, char *argv[])
{
    DWORD threadID;
    HANDLE hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &threadID); // 创建线程
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread); // 关闭内核对象
    return 0;
}