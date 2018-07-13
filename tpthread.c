#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>

#define	MAX_NUM		100
static pthread_t	gpid[MAX_NUM];

void *thread_routine(void *arg)
{
	printf("enter thread routine\n");
	usleep(1000);
	printf("exit thread_routine\n");
	return NULL;
}

void handle_sigint(int signo)
{
	int ret;
	int i;
	printf("handle a signal %d\n", signo);
	for (i = 0; i < MAX_NUM; ++i)
	{
		ret = pthread_join(gpid[i], NULL);
		printf("signal process exit, ret = %d, %d\n", ret, EINVAL);
	}
}

int main(int argc, char *argv[])
{
	int ret;
	int	i,j;
	signal(SIGINT, handle_sigint);
	while (1)
	{
		for (i = 0; i < MAX_NUM; ++i)
			pthread_create(&gpid[i], NULL, thread_routine, NULL);
		for (i = 0; i < MAX_NUM; ++i)
			pthread_join(gpid[i], NULL);
		usleep(100000);
	}
	printf("main over\n");
}
