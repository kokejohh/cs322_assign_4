#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int fd[2];
	int n;
	pid_t pid;
	char line[100];

	if (pipe(fd) < 0)
		printf("pipe error\n");
	if ((pid = fork()) < 0) {
		printf("fork error\n");
	} else if (pid > 0) {
		close(fd[0]);
		write(fd[1], "hello world\n", 12);	
	} else {
		close(fd[1]);
		n = read(fd[0], line, 100);
		write(STDOUT_FILENO, line, n);
	}
	exit(0);
}
