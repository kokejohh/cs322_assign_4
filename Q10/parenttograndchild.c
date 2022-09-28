#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_LINE 255

int main()
{
	int fd[2];
	pid_t pid;
	int n;
	int status;
	char line[MAX_LINE];
	
	if (pipe(fd) < 0)
		printf("pipe error\n");
	if ((pid = fork()) < 0)
		printf("fork error\n");
	else if (pid == 0)
	{
		if ((pid = fork()) < 0)
			printf("fork error\n");
		else if (pid == 0)
		{
			close(fd[1]);
			n = read(fd[0], line, MAX_LINE);
			write(STDOUT_FILENO, line, n);		
			exit(0);
		}
		waitpid(pid, &status, 0);
	}
	else
	{
		close(fd[0]);
		write(fd[1], "hello grandchild\n", 17);
		waitpid(pid, &status, 0);
	}
	exit(0);
}
