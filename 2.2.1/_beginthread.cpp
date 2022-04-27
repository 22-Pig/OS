#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <tchar.h>

void __cdecl ThreadProc(void *para)
{
    printf("sub thread started\n");
    printf("sub thread finished\n");
    _endthread(); // 可以省略，隐含会调用。
}
int _tmain(int argc, _TCHAR *argv[])
{
    HANDLE hThread = (HANDLE)_beginthread(ThreadProc, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);
    return 0;
}
