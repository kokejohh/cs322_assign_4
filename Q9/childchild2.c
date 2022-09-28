#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_LINE 255

int main()
{
	int fd[2], fd2[2];
	pid_t pid[2] = {55, 54};
	int n;
	int status;
	char line[MAX_LINE];
	
	if (pipe(fd) < 0 || pipe(fd2) < 0)
		printf("pipe error\n");
	if ((pid[0] = fork()) < 0 || (pid[1] = fork()) < 0)
		printf("fork error\n");
	if (pid[0] == 0)
	{
		close(fd[0]);
		close(fd2[1]);
		printf("child \n");
		write(fd[1], "ping\n", 5);
		n = read(fd2[0],line, MAX_LINE);
		write(STDOUT_FILENO, line, n);
		exit(0);
	}
	if (pid[1] == 0)
	{
		close(fd[1]);
		close(fd2[0]);
		printf("child2\n");
		n = read(fd[0], line, MAX_LINE);
		write(STDOUT_FILENO, line, n);
		write(fd2[1], "pong\n", 5);
		exit(0);
	}
	exit(0);
}
