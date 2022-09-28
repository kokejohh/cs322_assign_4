#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(void *ptr, int total_space);

int main()
{
	int total_space = 10;
	int add_space = 0;
	void *ptr = malloc(total_space);
	void *ptr2 = calloc(1, total_space);
	memset(ptr, 'a', total_space);
	
	printf("ptr : ");
	print(ptr, total_space);
	printf("ptr2 : ");
	print(ptr2, total_space);
	
	while (add_space > -1)
	{
		printf("Input add_space : ");
		scanf("%d", &add_space);
		if (add_space > 0)
		{
			total_space = total_space + add_space;
			ptr = realloc(ptr, total_space);
			memset(ptr, 'a', total_space);
			printf("ptr after add_space : ");
			print(ptr, total_space);
		}
	}
	return (0);
}

void print(void *ptr, int total_space)
{
	for (int i = 0; i < total_space; i++)
		printf("%d ", ((char *)ptr)[i]);
	printf("\n");
}
