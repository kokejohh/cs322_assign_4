#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LINE 255

int main()
{
	int fd[2];
	pid_t pid;
	int n;
	char line[MAX_LINE];	
	
	if (pipe(fd) < 0)
		printf("pipe error\n");
	if ((pid = fork()) < 0)
		printf("fork error\n");
	else if (pid == 0)
	{
		close(fd[0]);
		write(fd[1], "hello from child\n", 17);	
	}
	else
	{
		close(fd[1]);
		n = read(fd[0], line, MAX_LINE);
		write(STDOUT_FILENO, line, n);
	}
	exit(0);
}
