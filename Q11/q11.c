#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 255

int main(int argc, char *argv[])
{
	int fd[2], n;
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
		exit(0);
	}
	else
	{
		close(fd[1]);
		if (fd[0] != STDIN_FILENO)
		{
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
				printf("dup2 error to stdin\n");
			close(fd[0]);
		}
		
		if (execl("/bin/wc", "wc", "-l", NULL) < 0)
			printf("execl error for %s\n", "test");
	}
	exit(0);
}
