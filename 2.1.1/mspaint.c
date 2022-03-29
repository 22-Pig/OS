#include <stdio.h>
#include <windows.h>

int main(int argc, char const *argv[])
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si)); /* 分配内存 */
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    if (!CreateProcess(("C:\\Windows\\System32\\mspaint.exe"),
                       NULL,
                       NULL,
                       NULL,
                       FALSE,
                       0,
                       NULL,
                       NULL,
                       &si,
                       &pi))
    {
        fprintf(stderr, "Create Process Failed");
        return -1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    printf("child Complete");
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
