#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void sig_chld(int n);

int main()
{
	pid_t pid;
	
	if ((pid = fork()) < 0)
		printf("fork error\n");
	else if (pid == 0)
	{
		int index = 0;
		for(;;)
		{
			printf("Index : %d\n", index++);
			sleep(3);
		}
	}
	else
	{
		if (signal(SIGCHLD, sig_chld) == SIG_ERR)
			printf("signal error\n");
		while(1);
	}
}

void sig_chld(int n)
{
	int status;
	waitpid(0, &status, 0);
	printf("Got sigchld (%d)\n", n);
	sleep(10);
	exit(1);
}
