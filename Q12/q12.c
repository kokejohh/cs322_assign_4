#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 255
#define DEF_PAGER "/bin/more"

int main(int argc, char *argv[])
{
	int fd[2], fd2[2], n;
	pid_t pid;
	char *pager, *argv0;
	char line[MAX_LINE];
	FILE *fp;

	if (argc != 2)
		printf("argment error\n");
	if ((fp = fopen(argv[1], "r")) == NULL)
		printf("can't open %s\n", argv[1]);
	if (pipe(fd) < 0)
		printf("pipe error\n");
	if ((pid = fork()) < 0)
		printf("fork error\n");
	else if (pid > 0)
	{
		close(fd[0]);
		close(fd2[1]);
		while (fgets(line, MAX_LINE, fp) != NULL)
		{
			n = strlen(line);
			if (write(fd[1], line, n) != n)
				printf("write error to pipe\n");
		}
		if (ferror(fp))
			printf("fgets error\n");
		close(fd[1]);
		if (waitpid(pid, NULL, 0) < 0)
			printf("waitpid error\n");
		
		n = read(fd2[0], line, MAX_LINE);
		write(STDOUT_FILENO, line, n);
		exit(0);
	}
	else
	{
		close(fd[1]);
		close(fd2[0]);
		if (fd[0] != STDIN_FILENO)
		{
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
				printf("dup2 error to stdin\n");
			close(fd[0]);
		}
		
		write(1, "test\n", 5);		
		if (execl("/bin/wc", "wc", "-l", NULL) < 0)
			printf("execl error for %s\n", "test");
/*
		if (fd2[1] != STDOUT_FILENO)
		{
			if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
				printf("dup2 error to stdout\n");
			close(fd2[1]);
		}
*/
	}
	exit(0);
}
