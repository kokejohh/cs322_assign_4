#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void scrapper();

int main(int argc, char *argv[])
{
	if (argc == 2)
	{	
		if (atexit(scrapper))
			printf("can't register scrapper\n");
	}
	else if (argc == 3)
	{
		if (strcmp(argv[2], "1") == 0)
			if (atexit(scrapper))
				printf("can't register scrapper\n");
	}
	else
	{
		printf("error argument\n");
		return (0);
	}
	char *str = " > commandstr.txt";
	strcat(argv[1], str);
	system(argv[1]);
	return (0);	
}

void scrapper()
{
	system("rm commandstr.txt");
}
