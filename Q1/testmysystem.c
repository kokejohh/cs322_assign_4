#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc == 2)
		system(argv[1]);
	else
		printf("error argument\n");
	return (0);
}
