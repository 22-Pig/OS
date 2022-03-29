#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int pid;
	// fork系统调用用于创建一个新进程，称为子进程，它与进行fork()调用的进程(父进程)并发运行。
	pid = fork();
	switch (pid)
	{
	// 负值：创建子进程失败。
	case -1:
		printf("fork fail!\n");
		exit(1);
	// 零：返回到新创建的子进程。
	case 0:
		sleep(1);
		printf("Is son:\n");
		execl("/bin/ls", "ls", "-l", NULL);
		printf("exec fail!\n");
		exit(1);
	// 正值：返回给父亲或调用者。该值包含新创建子进程的进程ID。
	default:
		printf("Is parent:\n");
		// wait(0);
		while (1)
		{
			sleep(1);
		}
		exit(0);
	}
	return 0;
}
