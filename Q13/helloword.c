#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *hello_world(void *a)
{
	printf("hello world\n");
	return NULL;
}

int main()
{
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, hello_world, NULL);
	pthread_join(thread_id, NULL);
	exit(0);
}
