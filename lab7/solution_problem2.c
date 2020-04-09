#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>


void hup_signal()
{
	time_t curtime;
	time(&curtime);

	printf("%s\n", ctime(&curtime));
}


int main()
{
	printf("I'm %d\n", getpid());
	signal(SIGHUP, hup_signal);

	while(1)
	{
		sleep(1);
	}

	return 0;
}

